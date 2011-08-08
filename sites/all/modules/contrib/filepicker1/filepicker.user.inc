<?php

/**
 * @file
 * my filepicker in my account
 */
function filepicker_user_page($uid, $path="", $func="", $id=0) {
  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');
  drupal_add_js(FILEPICKER_PATH .'/filepicker.js');
  $content = '';
  // path/func/id
  if ($path == 'files') {
    if ($func == 'list' && is_numeric($id) && $id > 0) {
      $content .= filepicker_user_view($id);
    }
    elseif ($func == 'edit' && is_numeric($id) && $id > 0) {
      module_load_include('inc', 'filepicker', 'filepicker.edit');
      $content .= filepicker_user_file_edit($id);
    }
    elseif ($func == 'list_public') {
      if (is_numeric($id) && $id > 0) {
        $content .= filepicker_user_view_public($id);
      }
      else {
        $content .= filepicker_user_list_public();
      }
    }
    elseif ($func == 'list') {
      $content .= filepicker_user_list_admin();
    }
    elseif ($func == 'delete' && is_numeric($id) && $id > 0) {
      filepicker_file_delete($id, FALSE, 'account');
    }
  }
  elseif (variable_get('filepicker_groups_enabled', 1) && $path == 'groups') {
    module_load_include('inc', 'filepicker', 'filepicker.group');
    if ($func == 'edit' && is_numeric($id) && $id > 0) {
      $content .= filepicker_user_groups($func, $id);
    }
    elseif ($func == 'list' && is_numeric($id) && $id > 0) {
      filepicker_set_user_group_state(1, $id);
      $content .= filepicker_user_groups();
    }
    elseif ($func == 'list') {
      $content .= filepicker_user_groups();
    }
    elseif ($func == 'delete') {
      $content .= drupal_get_form('filepicker_group_delete_form', $id);
    }
  }
  elseif ($path == 'stats') {
    $content .= filepicker_group_stats(-1);
  }
  elseif ($path == 'config') {
    $content .= filepicker_user_config_admin();
  }
  else {
    module_load_include('inc', 'filepicker', 'filepicker.upload');
    $content .= filepicker_user_upload();
  }
  return $content;
}

function filepicker_user_list_public() {
  $content = _filepicker_list_admin("account", FALSE, TRUE);
  return $content;
}

function filepicker_user_list_admin() {
  $content = _filepicker_list_admin("account");
  return $content;
}

function filepicker_user_view($file_id) {
  drupal_add_js(FILEPICKER_PATH .'/filepicker.js');

  $file = _filepicker_get_file($file_id);
  if ($file) {
    $filepath = filepicker_get_file_path($file);
    $info = filepicker_get_info($file);
    $view = theme('filepicker_view', $file, $filepath, $info);
    $form1 = drupal_get_form('filepicker_user_file_form', $file_id);
    $form2 = '';
    $form3 = '';
    // group form
    if (_filepicker_has_groups()) {
      $form3 = drupal_get_form('filepicker_group_files_form', $file['file_id']);
    }
    $content = theme('filepicker_user_view', $view, $form1, $form2, $form3);
  }
  else {
    drupal_set_message(t('File not found.'), 'error');
    $content = '';
  }
  return $content;
}

function filepicker_user_view_public($file_id) {

  $file = _filepicker_get_file($file_id, FALSE);
  if ($file) {

    $result = db_query("SELECT name FROM {users} WHERE uid=%d AND status=1", array($file['uid']));
    $row = db_fetch_array($result);
    $file['name'] = ($row['name'] ? $row['name'] : FALSE);

    $filepath = filepicker_get_file_path($file, 'full', array('name' => $file['name'] , 'uid' => $file['uid'] ));
    $info = filepicker_get_info(filepicker_get_path(FALSE, array('name' => $file['name'] , 'uid' => $file['uid'] )) . $file['file_name']);
    $content = theme('filepicker_view', $file, $filepath, $info);
  }
  else {
    drupal_set_message(t('File not found.'), 'error');
    $content = '';
  }
  return $content;
}

function filepicker_user_file_form(&$form_state, $file_id) {
  $form['edit'] = array(
    '#type' => 'submit',
    '#value' => t('Edit file'),
    '#submit' => array('filepicker_user_file_form_edit'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete file'),
    '#submit' => array('filepicker_user_file_form_delete'),
  );
  $form['file_id'] = array(
    '#type' => 'value',
    '#value' => $file_id,
  );
  return $form;
}

function filepicker_user_file_form_delete($form, &$form_state) {
  filepicker_file_delete($form_state['values']['file_id'] , FALSE, 'account');
}

function filepicker_user_file_form_edit($form, &$form_state) {
  global $user;
  drupal_goto('user/'. $user->uid .'/filepicker/files/edit/'. $form_state['values']['file_id']);
}

/**
 * Menu callback; presents the configuration settings form for filepicker user.
 */
function filepicker_user_config_admin() {
  $content = drupal_get_form('filepicker_user_config_admin_form');
  return theme('filepicker_user_config', $content, '', t('Filepicker configuration page.'), '', '');
}

/**
 * Submit form
 */
function filepicker_user_config_admin_form(&$form_state, $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $form['#attributes']['enctype'] = 'multipart/form-data';

  // default options
  $form['filepicker_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set filepicker defaults'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -38,
  );
  $form['filepicker_defaults']['filepicker_rows_per_page'] = filepicker_rows_per_page_elem((isset($user->filepicker_rows_per_page) ? $user->filepicker_rows_per_page : NULL));


  // Iframe
  $form['filepicker_iframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filepicker Iframe settings'),
    '#description' => t('You can alter the default styling of the iframe here,<br />useful if the iframe is not fitting in with your theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -22,
  );
  if (module_exists('colorbox') && variable_get('colorbox_load', 0)) {
    $form['filepicker_iframe']['filepicker_advanced_colorbox'] = filepicker_colorbox_elem((isset($user->filepicker_advanced_colorbox) ? $user->filepicker_advanced_colorbox : NULL));
  }
  $form['filepicker_iframe']['filepicker_advanced_iframe_width'] = filepicker_iframe_width_elem((isset($user->filepicker_advanced_iframe_width) ? $user->filepicker_advanced_iframe_width : NULL));
  $form['filepicker_iframe']['filepicker_advanced_iframe_height'] = filepicker_iframe_height_elem((isset($user->filepicker_advanced_iframe_height) ? $user->filepicker_advanced_iframe_height : NULL));
  $form['filepicker_iframe']['filepicker_advanced_iframe_border'] = filepicker_iframe_border_elem((isset($user->filepicker_advanced_iframe_border) ? $user->filepicker_advanced_iframe_border : NULL));
  $form['filepicker_iframe']['filepicker_advanced_collapsed'] = filepicker_collapsed_elem((isset($user->filepicker_advanced_collapsed) ? $user->filepicker_advanced_collapsed : NULL));

  if ($account) {
    $form['uid'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('filepicker_user_config_form_reset'),
  );
  return $form;
}

function filepicker_user_config_admin_form_validate($form, &$form_state) {
  if (isset($form_state['values']['uid']) && is_numeric($form_state['values']['uid']) ) {
    $user = user_load(array('uid' => $form_state['values']['uid']));
  }
  else {
    global $user;
  }
  if (drupal_strlen($form_state['values']['filepicker_rows_per_page']) && ! is_numeric($form_state['values']['filepicker_rows_per_page'])) {
    form_set_error('filepicker_rows_per_page', t('Rows per page must be a number'));
  }

  if (! is_numeric($form_state['values']['filepicker_advanced_iframe_height'])) {
    form_set_error('filepicker_advanced_iframe_height', t('The Iframe height must be a number'));
  }
  if (! drupal_strlen($form_state['values']['filepicker_advanced_iframe_width'])) {
    form_set_error('filepicker_advanced_iframe_width', t('You must fill in the Iframe width'));
  }
  if (! drupal_strlen($form_state['values']['filepicker_advanced_iframe_border'])) {
    form_set_error('filepicker_advanced_iframe_border', t('You must fill in the Iframe border'));
  }
  // also used by the filepicker admin form

  if (! empty($_FILES['files']['name']['file_upload'])) {
    module_load_include('inc', 'filepicker', 'filepicker.upload');
    if (!isset($_FILES['files']['tmp_name']['file_upload']) || !file_exists($_FILES['files']['tmp_name']['file_upload'])) {
      form_set_error('file_upload', t('Error while uploading file.'));
    }
    elseif (!filepicker_get_uploaded_file_extension('file_upload')) {
      form_set_error('file_upload', t('Illegal filetype.'));
    }
  }
}

function filepicker_user_config_admin_form_submit($form, &$form_state) {
  if (isset($form_state['values']['uid'])) {
    $user = user_load(array('uid' => $form_state['values']['uid']));
  }
  else {
    global $user;
  }

  user_save($user, array('filepicker_rows_per_page' => $form_state['values']['filepicker_rows_per_page']));

  if (isset($form_state['values']['filepicker_advanced_colorbox']) && module_exists('colorbox')) {
    user_save($user, array('filepicker_advanced_colorbox' => $form_state['values']['filepicker_advanced_colorbox']));
  }
  user_save($user, array('filepicker_advanced_iframe_width' => $form_state['values']['filepicker_advanced_iframe_width']));
  user_save($user, array('filepicker_advanced_iframe_height' => $form_state['values']['filepicker_advanced_iframe_height']));
  user_save($user, array('filepicker_advanced_iframe_border' => $form_state['values']['filepicker_advanced_iframe_border']));
  user_save($user, array('filepicker_advanced_collapsed' => $form_state['values']['filepicker_advanced_collapsed']));
  drupal_set_message(t('Configuration settings saved'));
}

function filepicker_user_config_form_reset($form, &$form_state) {
  global $user;
  user_save($user, array('filepicker_rows_per_page' => NULL));
  user_save($user, array('filepicker_advanced_colorbox' => NULL));
  user_save($user, array('filepicker_advanced_iframe_width' => NULL));
  user_save($user, array('filepicker_advanced_iframe_height' => NULL));
  user_save($user, array('filepicker_advanced_iframe_border' => NULL));
  user_save($user, array('filepicker_advanced_collapsed' => NULL));
  drupal_set_message(t('Configuration settings reset'));
}

function filepicker_user_config_admin_form_delete($form, &$form_state) {
  if ( $form_state['values']['uid'] ) {
    $user = user_load(array('uid' => $form_state['values']['uid']));
  }
  else {
    global $user;
  }
}

