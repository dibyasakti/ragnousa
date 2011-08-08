<?php

/**
 * @file
 * admin settings functions
 */

/**
 * Menu callback; presents the settings form for filepicker
 */
function filepicker_settings_page($op = NULL) {
  $content = drupal_get_form('filepicker_settings_form');
  return $content;
}

/**
 * Function to display the filepicker admin settings form
 * @return
 *   Returns the form.
 */
function filepicker_settings_form(&$form_state) {
  drupal_add_js(FILEPICKER_PATH .'/filepicker.js');
  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');

  // default settings
  $form['filepicker_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set filepicker settings'),
    '#description' => t('Overall administrative settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -40,
  );
  $node_types = node_get_types('names');
  $form['filepicker_settings']['filepicker_node_types_enabled'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node Types'),
    '#description' => t('Set the node types you want to enable Filepicker for.'),
    '#default_value' => variable_get('filepicker_node_types_enabled', array_keys($node_types)),
    '#options' => $node_types,
  );
  if (module_exists('comment')) {
    $form['filepicker_settings']['filepicker_comment_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Comments'),
      '#description' => t('Setting this option enables Filepicker in comments.'),
      '#return_value' => 1,
      '#default_value' => variable_get('filepicker_comment_enabled', 0),
    );
  }
  $form['filepicker_settings']['filepicker_blocks_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Blocks'),
    '#description' => t('Setting this option enables Filepicker in blocks.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_blocks_enabled', 0),
  );
  $form['filepicker_settings']['filepicker_account_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filepicker in My Account'),
    '#description' => t('Setting this option enables Filepicker in My Account.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_account_enabled', 1),
  );
  $form['filepicker_settings']['filepicker_user_config_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable User configuration'),
    '#description' => t('Allow users to select their own settings.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_user_config_enable', 1),
  );
  $form['filepicker_settings']['filepicker_use_full_url'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use full url'),
    '#description' => t('Setting this option will make filepicker use a full url to the file being inserted, unsetting it will use a path relative to the Drupal root.<br />This is useful if you are developing a site with a different url than the production site will be on.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_use_full_url', 0),
  );
  $form['filepicker_settings']['filepicker_use_new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open link in new window'),
    '#description' => t('Setting this option will set the inserted link to open in a new window.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_use_new_window', 0),
  );
  $form['filepicker_settings']['filepicker_use_icons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Icons in tables'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_use_icons', 1),
    '#description' => t('Setting this option enables icons in tables.'),
  );

  // default options
  $form['filepicker_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set filepicker defaults'),
    '#description' => t('These settings are also available to users if User Configuration is enabled.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -38,
  );
  $form['filepicker_defaults']['filepicker_rows_per_page'] = filepicker_rows_per_page_elem(variable_get('filepicker_rows_per_page', 25));

  $form['filepicker_defaults']['filepicker_dateformat_default'] = array(
    '#type' => 'select',
    '#title' => t('Set Date Format'),
    '#description' => t("Select the Date format to use in tables."),
    '#default_value' => variable_get('filepicker_dateformat_default', 'medium'),
    '#options' => array('small' => t('Small'), 'medium' => t('Medium'), 'large' => t('Long')),
  );

  $form['filepicker_defaults']['filepicker_upload_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted file extensions'),
    '#default_value' => variable_get('filepicker_upload_extensions', 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp'),
    '#maxlength' => 255,
    '#description' => t('Default extensions that users can upload. Separate extensions with a space and do not include the leading dot.'),
  );
  $form['filepicker_defaults']['filepicker_upload_mimetypes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Mimetype check'),
    '#description' => t('Setting this option will enable the built in Drupal mimetype checking.<br />This will prevent the type "application/octet-stream" from being downloaded.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_upload_mimetypes', 0),
  );
  // quota
  $form['filepicker_quotas'] = array(
    '#type' => 'fieldset',
    '#title' => t('User quotas'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -28,
  );
  $form['filepicker_quotas']['filepicker_quota_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Quotas in Filepicker'),
    '#description' => t('Setting this option will enable Quotas in Filepicker.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_quota_enable', 1),
  );
  $form['filepicker_quotas']['filepicker_quota_byrole'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Quotas by Role'),
    '#description' => t("Setting this option will enable 'Quotas by Role' instead of 'Per User'."),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_quota_byrole', 0),
  );
  $form['filepicker_quotas']['filepicker_quota_role'] = array(
    '#type' => 'radios',
    '#title' => t('Available Roles'),
    '#description' => t("Select which Role for 'Quotas by Role'."),
    '#options' => user_roles(TRUE),
    '#default_value' => variable_get('filepicker_quota_role', 2),
  );
  $form['filepicker_quotas']['filepicker_quota_default'] = array(
    '#type' => 'select',
    '#title' => t('Set Quota'),
    '#description' => t("Select the Quota to apply for 'Quotas by Role' or the default for 'Per User'."),
    '#default_value' => variable_get('filepicker_quota_default', 0),
    '#options' => filepicker_get_quota_list(),
  );
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
    $form['filepicker_iframe']['filepicker_advanced_colorbox'] = filepicker_colorbox_elem(variable_get('filepicker_advanced_colorbox', 0));
  }
  $form['filepicker_iframe']['filepicker_advanced_iframe_width'] = filepicker_iframe_width_elem(variable_get('filepicker_advanced_iframe_width', "100%"));
  $form['filepicker_iframe']['filepicker_advanced_iframe_height'] = filepicker_iframe_height_elem(variable_get('filepicker_advanced_iframe_height', "500"));
  $form['filepicker_iframe']['filepicker_advanced_iframe_border'] = filepicker_iframe_border_elem(variable_get('filepicker_advanced_iframe_border', "0"));
  $form['filepicker_iframe']['filepicker_advanced_collapsed'] = filepicker_collapsed_elem(variable_get('filepicker_advanced_collapsed', 0));


  // progress bar
  $form['filepicker_progress'] = array(
    '#type' => 'fieldset',
    '#title' => t('Progress bar'),
    '#description' => t('Enable and configure progress bar.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -18,
  );
  $form['filepicker_progress']['filepicker_upload_progress_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Progress bar in upload'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_upload_progress_enabled', 1),
  );
  $form['filepicker_progress']['filepicker_upload_progress_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Progress bar Delay'),
    '#description' => t('Show the progress bar if processing is longer than this value.'),
    '#size' => 3,
    '#required' => TRUE,
    '#default_value' => variable_get('filepicker_upload_progress_delay', 3),
    '#field_suffix' => t('seconds'),
  );

  $form['filepicker_progress']['filepicker_upload_progress_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Progress bar message'),
    '#description' => t('Message to display while uploading.'),
    '#size' => 60,
    '#default_value' => variable_get('filepicker_upload_progress_message', t('Processing form... please wait.')),
  );

  $vok = FALSE;
  $extok = FALSE;
  if (version_compare(phpversion(), FILEPICKER_UPLOAD_STATUS_MIN_PHP) >= 0 ) {
    $vok = TRUE;
    if (extension_loaded('uploadprogress')) {
      $extok = TRUE;
    }
  }
  if ($vok && $extok) {
    $form['filepicker_progress']['filepicker_uploadprogress'] = array(
      '#type' => 'fieldset',
      '#title' => t('Upload Progress Extension'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['filepicker_progress']['filepicker_uploadprogress']['filepicker_uploadprogress_server'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable PECL uploadprogress'),
      '#default_value' => variable_get('filepicker_uploadprogress_server', ''),
    );
    $form['filepicker_progress']['filepicker_uploadprogress']['filepicker_uploadprogress_interval'] = array(
      '#title' => t('Interval Time'),
      '#description' => t('The interval between each check.'),
      '#type' => 'textfield',
      '#size' => 5,
      '#default_value' => variable_get('filepicker_uploadprogress_interval', 1),
      '#field_suffix' => t('seconds'),
    );
  }

  // Groups
  $form['filepicker_groups'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filepicker group settings'),
    '#description' => t('Enable and configure groups.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -16,
  );
  $form['filepicker_groups']['filepicker_groups_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Groups'),
    '#description' => t('Allow users to manage groups.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_groups_enabled', 1),
  );
  $form['filepicker_groups']['filepicker_public_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Public option'),
    '#description' => t('Allow users to make file groups publicly available.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_public_enabled', 1),
  );
  $form['filepicker_groups']['filepicker_publicroles_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Public Role Control option'),
    '#description' => t('Allow users to make publicly available file groups restricted by role.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_publicroles_enabled', 1),
  );
  $form['filepicker_groups']['filepicker_groups_in_upload_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Groups in upload form'),
    '#description' => t('Allow users to select a group in the upload form.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_groups_in_upload_enabled', 1),
  );
  // Import
  $form['filepicker_import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filepicker Bulk Import'),
    '#description' => t('Enable bulk import of files.'),
    '#collapsible' => TRUE,
    '#collapsed' => (variable_get('filepicker_import_enabled', 0) ? TRUE : FALSE),
    '#weight' => -14,
  );
  $form['filepicker_import']['filepicker_import_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Bulk import processing'),
    '#description' => t('Import files into filepicker from an import folder in the filesystem.<br />Requires FTP or SSH access'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_import_enabled', 0),
  );
  $form['filepicker_import']['filepicker_import_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Bulk import deletion'),
    '#description' => t('Delete uploaded source files after succesful import into filepicker.<br />The files should be writeable by the web server for this option to work.'),
    '#return_value' => 1,
    '#default_value' => variable_get('filepicker_import_delete', 0),
  );
  $form['filepicker_import']['filepicker_import_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Import Batch size'),
    '#description' => t('How many files to process at a time. Must be greater than 1 and less than 100.'),
    '#size' => 3,
    '#required' => TRUE,
    '#default_value' => variable_get('filepicker_import_max', 5),
  );

  $form = system_settings_form($form);
  unset($form['#theme']);
  return $form;
}

/**
 * Validate settings form
 */
function filepicker_settings_form_validate($form, &$form_state) {
  global $user;
  if (! is_numeric($form_state['values']['filepicker_rows_per_page']) || $form_state['values']['filepicker_rows_per_page'] < 1 ) {
    form_set_error('filepicker_rows_per_page', t('The rows per page field must be greater than one.'));
  }
  if (! is_numeric($form_state['values']['filepicker_advanced_iframe_height']) || $form_state['values']['filepicker_advanced_iframe_height'] < 1 ) {
    form_set_error('filepicker_advanced_iframe_height', t('The Iframe height must be a positive number'));
  }
  if (! drupal_strlen($form_state['values']['filepicker_advanced_iframe_width'])) {
    form_set_error('filepicker_advanced_iframe_width', t('You must fill in the Iframe width'));
  }
  if (! drupal_strlen($form_state['values']['filepicker_advanced_iframe_border'])) {
    form_set_error('filepicker_advanced_iframe_border', t('You must fill in the Iframe border'));
  }
  if (! is_numeric($form_state['values']['filepicker_upload_progress_delay']) || $form_state['values']['filepicker_upload_progress_delay'] < 0) {
    form_set_error('filepicker_upload_progress_delay', t('The progress delay must be a positive number or zero'));
  }
  if (isset($form_state['values']['filepicker_uploadprogress_interval'])) {
    if ( ! is_numeric($form_state['values']['filepicker_uploadprogress_interval']) || $form_state['values']['filepicker_uploadprogress_interval'] < 1) {
      form_set_error('filepicker_uploadprogress_interval', t('The progress interval must be a positive number'));
    }
  }
  if (! is_numeric($form_state['values']['filepicker_import_max']) || ($form_state['values']['filepicker_import_max'] < 1 || $form_state['values']['filepicker_import_max'] > 100 )) {
    form_set_error('filepicker_import_max', t('The Import batch size must be must be a positive number.'));
  }

  if ($form_state['values']['filepicker_groups_enabled'] != 1) {
    $form_state['values']['filepicker_public_enabled'] = 0;
    $form_state['values']['filepicker_publicroles_enabled'] = 0;
    $form_state['values']['filepicker_groups_in_upload_enabled'] = 0;
  }
  if ($form_state['values']['filepicker_quota_enable'] != 1) {
    $form_state['values']['filepicker_quota_byrole'] = 0;
  }
}

/**
 * Administration functions
 */
function filepicker_admin_users_list($dir, $label='') {

  $how_many = variable_get('filepicker_rows_per_page', 25);
  $header = array(
    array('data' => t('Name'), 'field' => 'u.name'),
    t('Files'),
    (variable_get('filepicker_groups_enabled', 1) ? t('Groups') : ''),
    (variable_get('filepicker_quota_enable', 1) ? t('Quotas') : ''),
    t('Used'),
  );
  $cols = 5;
  $rowcount = 0;
  $rows = '';

  $countsql = "SELECT COUNT(DISTINCT u.uid) FROM {filepicker} i JOIN {users} u ON i.uid=u.uid WHERE u.status=1";
  $sql = "SELECT DISTINCT u.uid, u.name FROM {filepicker} i JOIN {users} u ON  i.uid=u.uid WHERE u.status=1";
  $sql .= tablesort_sql($header);
  $result = pager_query($sql, $how_many, 0, $countsql);

  while ($row = db_fetch_array($result)) {
    $account = user_load( array('uid' => $row['uid']));
    $allcount = _filepicker_user_has_file($account);
    $groupcount = _filepicker_user_has_groups('all', $account);
    $usedbytesprint = _filepicker_bkmg(filepicker_get_all_bytes($account)+1);
    $quota = 0;
    if (variable_get('filepicker_quota_enable', 1)) {
      if (variable_get('filepicker_quota_byrole', 0)) {
        $roleid = variable_get('filepicker_quota_role', 2);
        if (filepicker_user_has_role($roleid, $account) && $account->uid > 1) {
          $quota = variable_get('filepicker_quota_default', 0);
        }
      }
      else {
        $quota = (isset($account->filepicker_quota) ? $account->filepicker_quota : variable_get('filepicker_quota_default', 0));
      }
    }

    $row_data = array(
      check_plain($row['name']),
      ($allcount ? $allcount .' '. l(t('files'), FILEPICKER_ADMIN_PATH .'/files/user/'. $row['uid'] .'/list' ) : t('No files')),
      (variable_get('filepicker_groups_enabled', 1) ? ($groupcount ? ($groupcount .' '. l(t('groups'), FILEPICKER_ADMIN_PATH .'/groups/user/'. $row['uid'] .'/list' )) : t('No groups')) : ''),
      (variable_get('filepicker_quota_enable', 1) ? l(filepicker_get_quota_list($quota+1), FILEPICKER_ADMIN_PATH .'/files/user/'. $row['uid'] .'/quota') : ''),
      $usedbytesprint,
    );
    $rows[] = $row_data;
    $rowcount++;
  }

  return theme('filepicker_list', $header, $rows, $how_many, t('No users found.'), '', '', $label, $cols);
}

function filepicker_admin_groups_list($label="") {
  $how_many = variable_get('filepicker_rows_per_page', 25);
  $use_icons = variable_get('filepicker_use_icons', 1);
  $header = array(
    array('data' => t('Group Name'), 'field' => 'g.group_name'),
    array('data' => t('User Name'), 'field' => 'u.name'),
    array('data' => t('Status'), 'field' => 'g.public'),
    array('data' => t('Files'), 'field' => 'ct'),
    array('data' => t('Actions'), 'colspan' => 2),
  );
  $cols = 6;
  $rowcount = 0;
  $rows = '';

  $countsql = "SELECT COUNT(g.gid) FROM {filepicker_user_groups} g JOIN {users} u USING(uid)";
  $sql = "SELECT g.gid, g.uid, g.group_name, g.group_description, g.state, g.public, u.name
    FROM {filepicker_user_groups} g JOIN  {users} u USING(uid)";
  $sql .= tablesort_sql($header);
  $result = pager_query($sql, $how_many, 0, $countsql);

  while ($row = db_fetch_array($result)) {
    $editpath = FILEPICKER_ADMIN_PATH .'/groups/user/'. $row['uid'] .'/edit/'. $row['gid'];
    $deletepath = FILEPICKER_ADMIN_PATH .'/groups/user/'. $row['uid'] .'/delete/'. $row['gid'];
    $filect = filepicker_group_files_count($row['gid']);
    $row_data = array(
      $row['group_name'],
      l($row['name'], FILEPICKER_ADMIN_PATH .'/groups/user/'. $row['uid']),
      ($row['public'] ? t('Public') : t('Private')),
      ($filect ? l(format_plural($filect, '1 file', '@count files'), FILEPICKER_ADMIN_PATH .'/groups/user/'. $row['uid'] .'/list/'. $row['gid'] ) : t('No files')),
      ($use_icons ? _filepicker_get_icon('edit', $editpath, array('title' => t('Edit'))) : l(t('Edit'), $editpath)),
      ($use_icons ?  _filepicker_get_icon('delete', $deletepath, array('title' => t('Delete'))) : l(t('Delete'), $deletepath)),
    );
    $rows[] = $row_data;
    $rowcount++;
  }

  $pref = '';
  $suff = '';
  return theme('filepicker_list', $header, $rows, $how_many, t('No groups found.'), $pref, $suff, $label, $cols);
}

function filepicker_admin_view($file_id, $account = FALSE) {
  if ($account) {
    $user = $account;
    $userdir = array('name' => $user->name , 'uid' => $user->uid);
  }
  else {
    global $user;
    $userdir = FALSE;
  }
  $file = _filepicker_get_file($file_id, FALSE, $user);
  if ($file) {
    $filepath = filepicker_get_file_path($file, 'full', $userdir);
    $info = filepicker_get_info($file);
    $view = theme('filepicker_view', $file, $filepath, $info);
    $form1 = drupal_get_form('filepicker_admin_file_form', $file_id, $user);
    $form2 = '';
    $form3 = '';
    // group form
    if (_filepicker_has_groups($user)) {
      $form3 = drupal_get_form('filepicker_group_files_form', $file['file_id'], $user);
    }
    $content = theme('filepicker_admin_view', $view, $form1, $form2, $form3);
  }
  else {
    drupal_set_message(t('File not found.'), 'error');
    $content = '';
  }
  return $content;
}

/**
 * Function to display the file edit/delete form
 * @return
 *   Returns the form.
 */
function filepicker_admin_file_form(&$form_state, $file_id, $account = FALSE) {
  if ($account) {
    $form['account'] = array(
      '#type' => 'value',
      '#value' => $account->uid,
    );
  }
  $form['file_id'] = array(
    '#type' => 'value',
    '#value' => $file_id,
  );
  $form['edit'] = array(
    '#type' => 'submit',
    '#value' => t('Edit file'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete file'),
  );
  return $form;
}

function filepicker_admin_file_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Delete file')) {
    $account = user_load(array('uid' => $form_state['values']['account']));
    filepicker_file_delete($form_state['values']['file_id'], $account, 'admin');
  }
  elseif ($form_state['values']['op'] == t('Edit file')) {
    drupal_goto(FILEPICKER_ADMIN_PATH .'/files/user/'. $form_state['values']['account'] .'/edit/'. $form_state['values']['file_id'] .'');
  }
}

/**
 * Function to display the filepicker user search form
 * @return
 *   Returns the form.
 */
function filepicker_user_search_form(&$form_state, $dir) {
  $form['filepicker_currentuser'] = array(
    '#type' => 'textfield',
    '#title' => t('Users'),
    '#autocomplete_path' => FILEPICKER_ADMIN_PATH .'/'. $dir .'/autocomplete',
    '#default_value' => '',
    '#maxlength' => 30,
    '#size' => 25,
  );
  $form['dir'] = array(
    '#type' => 'value',
    '#value' => $dir,
  );
  $form['filepicker_user_search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );
  return $form;
}

function filepicker_user_search_form_submit($form, &$form_state) {
  if ($form_state['values']['filepicker_currentuser']) {
    if ($form_state['values']['dir'] == 'import') {
      $result = db_query("SELECT u.uid FROM {users} u WHERE u.name = '%s'", $form_state['values']['filepicker_currentuser']);
    }
    else {
      $result = db_query("SELECT u.uid FROM {users} u, {filepicker} i WHERE u.name = '%s' AND u.uid=i.uid", $form_state['values']['filepicker_currentuser']);
    }

    $row = db_fetch_array($result);
    if ($row['uid'] ) {
      variable_set('filepicker_currentuser', $row['uid']);
      drupal_goto(FILEPICKER_ADMIN_PATH .'/'. $form_state['values']['dir'] .'/user/'. $row['uid'] .'/list');
    }
    else {
      variable_del('filepicker_currentuser');
    }
  }
  else {
    variable_del('filepicker_currentuser');
  }
}


function filepicker_admin_groups() {
  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');
  module_load_include('inc', 'filepicker', 'filepicker.group');
  if (! arg(4) ) {
    variable_del('filepicker_currentuser');
    variable_set('filepicker_currentgroup', 0);
    $action = 'users';
  }
  $uid = variable_get('filepicker_currentuser', '');
  if ( arg(4) == 'user' && is_numeric(arg(5))) {
    $uid = arg(5);
  }
  elseif (arg(4) == 'stats' || arg(4) == 'users') {
    $action = arg(4);
  }
  $gidaction = '';
  $gid = 0;
  if ( (arg(6) == 'list' || arg(6) == 'edit' || arg(6) == 'delete') && is_numeric(arg(7)) ) {
    $gidaction = arg(6);
    $gid = arg(7);
    if (arg(6) == 'list') {
      variable_set('filepicker_currentgroup', $gid);
      drupal_goto(FILEPICKER_ADMIN_PATH .'/files/user/'. $uid .'/list');
    }
  }
  $name = '';
  $content = '';
  if ($uid) {
    $account = user_load(array('uid' => $uid));
    $name = $account->name;
  }
  if (variable_get('filepicker_groups_enabled', 1)) {
    $content .= drupal_get_form('filepicker_group_search_form');
    $content .= '<p>'. t('Managing groups for ') . ($name ? l($name, "user/$uid") : 'All') .'</p>';
    if ($uid) {
      // show groups for $uid
      if ($gid) {
        if ($gidaction == 'edit') {
          $record = filepicker_get_user_group($gid);
          $content .= drupal_get_form('filepicker_groups_form', $record);
        }
        elseif ($gidaction == 'delete') {
          $content .= drupal_get_form('filepicker_group_delete_form', $gid);
        }
      }
      elseif (arg(6) == 'stats') {
        $content .= filepicker_group_stats($account, t('Statistics for %name', array('%name' => $name)));
      }
      else {
        $content .= filepicker_groups_list('admin', $account, t('Groups for %name', array('%name' => $name)));
        $content .= drupal_get_form('filepicker_groups_form', 0, $account);
      }
    }
    else {
      if ($action == 'stats') {
        $content .= filepicker_group_stats(FALSE, t('Statistics'));
      }
      else {
        $content .= filepicker_admin_groups_list(t('Groups'));
      }
    }
  }
  return $content;
}

function filepicker_admin_files() {
  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');
  if (! arg(4) ) {
    variable_del('filepicker_currentuser');
    variable_set('filepicker_currentgroup', 0);
    $action = 'users';
  }
  $uid = variable_get('filepicker_currentuser', '');
  if ( arg(4) == 'user' && is_numeric(arg(5))) {
    $uid = arg(5);
  }
  elseif (arg(4) == 'list_all' || arg(4) == 'stats' || arg(4) == 'users' || arg(4) == 'list_all') {
    $action = arg(4);
    variable_del('filepicker_currentuser');
    variable_set('filepicker_currentgroup', 0);
    $uid = variable_get('filepicker_currentuser', '');
  }
  $fileaction = '';
  if ( arg(6) == 'list_all'
    || arg(6) == 'edit'
    || arg(6) == 'delete'
    || arg(6) == 'list'
    || arg(6) == 'upload'
    || arg(6) == 'stats'
    || arg(6) == 'groups'
    || arg(6) == 'quota') {
    $fileaction = arg(6);
  }
  $file_id = 0;
  if ( is_numeric(arg(7))) {
    $file_id = arg(7);
  }
  $content = '';
  if (arg(6) == 'upload' ) {
    module_load_include('inc', 'filepicker', 'filepicker.upload');
    if (variable_get('filepicker_upload_progress_enabled', 1)) {
      $content .= filepicker_upload_progress_get_script(variable_get('filepicker_upload_progress_delay', 0));
    }
  }
  $name = "";
  if ($uid) {
    $account = user_load(array('uid' => $uid));
    $name = $account->name;
  }
  $content .= drupal_get_form('filepicker_user_search_form', 'files');
  $content .= '<p>'. t('Managing files for ') . ($name ? l($name, "user/$uid") : 'All') .'</p>';
  if ($uid) {
    if ($file_id) {
      if ($fileaction == 'edit' ) {
        module_load_include('inc', 'filepicker', 'filepicker.edit');
        $file =  _filepicker_get_file($file_id, FALSE, $account);
        $content .= theme('filepicker_file_edit_header', $file);
        $content .= drupal_get_form('filepicker_edit_form', $file, 'admin', $account);
      }
      elseif ($fileaction == 'delete') {
        filepicker_file_delete($file_id, $account, 'admin');
      }
      else {
        $content .= filepicker_admin_view($file_id, $account);
      }
    }
    elseif ($fileaction == 'upload') {
      $content .= filepicker_quota_ok('admin', $account, t('Upload file for %name', array('%name' => $name)));
    }
    elseif ($fileaction == 'stats') {
      $content .= filepicker_group_stats($account, t('Statistics for %name', array('%name' => $name)));
    }
    elseif ($fileaction == 'list') {
      $content .= _filepicker_list_admin('admin', $account, FALSE, 1, t('List files for %name', array('%name' => $name)));
    }
    elseif ($fileaction == 'quota') {
      $usedbytes = filepicker_get_all_bytes($account)+1;
      $usedbytesprint = _filepicker_bkmg($usedbytes);
      $quota = 0;
      if (variable_get('filepicker_quota_enable', 1)) {
        if (variable_get('filepicker_quota_byrole', 0)) {
          $roleid = variable_get('filepicker_quota_role', 2);
          if (filepicker_user_has_role($roleid, $account) && $account->uid > 1) {
            $quota = variable_get('filepicker_quota_default', 0);
          }
        }
        else {
          $quota = (isset($account->filepicker_quota) ? $account->filepicker_quota : variable_get('filepicker_quota_default', 0));
        }
      }
      $label = t('Quota for %name', array('%name' => $name));
      $filetot = _filepicker_user_has_file($account);
      $pl = format_plural($filetot, '1 file', '@count files');
      if ($quota) {
        $pused = round($usedbytes / ($quota*1000000) * 100, 2);
        $message = t('User %name has used %pused percent or %usedbytesprint of quota %quotaprint and has %pl.', array('%name' => $name, '%pused' => $pused, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl, '%quotaprint' => filepicker_get_quota_list($quota+1)));
      }
      else {
        $message = t('User %name has used %usedbytesprint and has %pl.', array('%name' => $name, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
      }
      if (! variable_get('filepicker_quota_byrole', 0) ) {
        $form = drupal_get_form('filepicker_quota_form', $account);
      }
      else {
        $form = "";
      }
      $content .= theme('filepicker_quota', $form, $message, $label);
    }
    elseif ($fileaction == 'groups') {
      drupal_goto(FILEPICKER_ADMIN_PATH .'/groups/user/'. $uid);
    }
    else {
      $content .= _filepicker_list('admin', $account, t('List files for %name', array('%name' => $name)));
    }
  }
  else {
    if ($action == 'stats') {
      $content .= filepicker_group_stats(FALSE, t('Statistics'));
    }
#    elseif ($action == 'list_all') {
#      $content .= _filepicker_list_public('admin', variable_get('filepicker_list_public', 0), t('List All Files'));
#    }
    elseif ($action == 'list_all') {
      $content .= _filepicker_list_admin('admin', FALSE, TRUE, variable_get('filepicker_list_public', 0), t('List All Files'));
    }
    else {
      $content .= filepicker_admin_users_list('files', t('Users'));
    }
  }
  return $content;
}

/**
 * Function to display the filepicker group search form
 * @return
 *   Returns the form.
 */
function filepicker_group_search_form(&$form_state, $dir = 'groups') {
  $form['filepicker_currentgroup'] = array(
    '#type' => 'textfield',
    '#title' => t('Groups'),
    '#description' => '',
    '#autocomplete_path' => FILEPICKER_ADMIN_PATH .'/groups/autocomplete',
    '#default_value' => '',
    '#maxlength' => 30,
    '#size' => 25,
  );
  $form['dir'] = array(
    '#type' => 'value',
    '#value' => $dir,
  );
  $form['filepicker_group_search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );
  return $form;
}

function filepicker_group_search_form_submit($form, &$form_state) {
  if ($form_state['values']['filepicker_currentgroup']) {
    $result = db_query("SELECT gid, uid FROM {filepicker_user_groups} WHERE group_name = '%s' ", $form_state['values']['filepicker_currentgroup']);
    $row = db_fetch_array($result);
    if ($row['gid'] ) {
      variable_set('filepicker_currentgroup', $row['gid']);
      drupal_goto(FILEPICKER_ADMIN_PATH .'/'. $form_state['values']['dir'] .'/user/'. $row['uid'] .'/edit/'. $row['gid']);
    }
    else {
      variable_set('filepicker_currentgroup', 0);
    }
  }
  else {
    variable_set('filepicker_currentgroup', 0);
  }
}

/**
 * Function to display the filepicker quota form
 * @return
 *   Returns the form.
 */
function filepicker_quota_form(&$form_state, $account=FALSE) {
  $list = filepicker_get_quota_list();
  $default = variable_get('filepicker_quota_default', 0);
  $quota = $default;
  $title = t('Set default quota');
  if ($account) {
    $title = t('Set user quota');
    $quota = (isset($account->filepicker_quota) && $account->filepicker_quota ? $account->filepicker_quota : $default);
  }
  $form['filepicker_quota'] = array(
    '#type' => 'select',
    '#default_value' => $quota,
    '#options' => $list,
    '#title' => $title,
  );
  $form['account'] = array(
    '#type' => 'value',
    '#value' => ($account ? $account->uid : 0),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );
  return $form;
}

function filepicker_quota_form_submit($form, &$form_state) {
    if ( $form_state['values']['account'] > 0 ) {
      $account = user_load(array('uid' => $form_state['values']['account']));
      user_save($account, array('filepicker_quota' => $form_state['values']['filepicker_quota']));
    }
    else {
      variable_set('filepicker_quota_default', $form_state['values']['filepicker_quota']);
    }
}

function filepicker_admin_import() {
  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');
  module_load_include('inc', 'filepicker', 'filepicker.import');
  if (! arg(4) ) {
    variable_del('filepicker_currentuser');
  }
  $uid = variable_get('filepicker_currentuser', '');
  if ( arg(4) == 'user' && is_numeric(arg(5))) {
    $uid = arg(5);
  }
  $content = "";
  if (! $importdir = variable_get('filepicker_import_dir', '')) {
    drupal_set_message(t('You need to set the import folder'));
  }
  $content = drupal_get_form('filepicker_import_dir_form');
  if ($importdir) {
    if ($import_files = filepicker_import_dir_check()) {
      $content .= drupal_get_form('filepicker_user_search_form', 'import');
      if ($uid) {
        $account = user_load(array('uid' => $uid));
        $content .= drupal_get_form('filepicker_import_form', count($import_files), $account, TRUE);
      }
      else {
        drupal_set_message(t('Please select a user. You have %total files to be imported', array('%total' => count($import_files)) ));
      }
    }
  }
  if ($msg = $_SESSION['filepicker_import_status']) {
    drupal_get_messages('status', TRUE);
    drupal_set_message($msg);
    unset($_SESSION['filepicker_import_status']);
  }
  return $content;
}

/**
 * Retrieve a pipe delimited string of autocomplete suggestions for existing users
 */
function filepicker_user_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    if (arg(3) == 'import') {
      $result = db_query_range("SELECT u.uid, u.name FROM {users} u WHERE LOWER(u.name) LIKE LOWER('%s%%')", $string, 0, 10);
    }
    else {
      $result = db_query_range("SELECT DISTINCT u.name FROM {users} u, {filepicker} i WHERE LOWER(u.name) LIKE LOWER('%s%%') AND u.uid=i.uid", $string, 0, 10);
    }
    while ($account = db_fetch_object($result)) {
      if (arg(3) == 'import') {
        $user = user_load(array('uid' => $account->uid));
        if (user_access('use filepicker', $user)) {
          $matches[$account->name] = check_plain($account->name);
        }
      }
      else {
        $matches[$account->name] = check_plain($account->name);
      }
    }
  }
  print drupal_to_js($matches);
  exit();
}

/**
 * Retrieve a pipe delimited string of autocomplete suggestions for existing groups
 */
function filepicker_group_search_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT group_name FROM {filepicker_user_groups} WHERE LOWER(group_name) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($group = db_fetch_object($result)) {
      $matches[$group->group_name] = check_plain($group->group_name);
    }
  }
  print drupal_to_js($matches);
  exit();
}
