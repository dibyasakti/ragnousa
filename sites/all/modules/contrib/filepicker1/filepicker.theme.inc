<?php

/**
 * @file
 * Theme functions for filepicker.
 */

/**
 * theme registry
 */
function filepicker_theme() {
  return array(
    'filepicker' => array(
      'arguments' => array('content' => NULL),
      'template' => 'filepicker',
    ),

    'filepicker_iframe' => array(
      'arguments' => array(
        'content' => NULL,
        'file'  => NULL,
        'public'  => NULL,
      ),
    ),
    'filepicker_list' => array(
      'arguments' => array(
        'header' => array(),
        'rows' => array(),
        'max' => 50,
        'message' => "",
        'pref' => "",
        'suff' => "",
        'label' => "",
      ),
    ),
    'filepicker_stats' => array(
      'arguments' => array(
        'header' => array(),
        'rows' => array(),
        'pref' => "",
        'suff' => "",
        'label' => "",
      ),
    ),
    'filepicker_fullpage' => array(
      'arguments' => array(
        'file' => array(),
        'source' => "",
        'link' => 1,
      ),
    ),
    'filepicker_quota_message' => array(
      'arguments' => array(
        'message1' => "",
        'message2' => "",
        'form' => array(),
        'label' => "",
        'help' => "",
      ),
    ),
    'filepicker_view' => array(
      'arguments' => array(
        'file' => array(),
        'filepath' => "",
        'info' => array(),
      ),
    ),
    'filepicker_file_edit_header' => array(
      'arguments' => array(
        'file' => array(),
      ),
    ),
    'filepicker_quota' => array(
      'arguments' => array(
        'form' => array(),
        'message' => "",
        'label' => "",
      ),
    ),
    'filepicker_user_config' => array(
      'arguments' => array(
        'form' => array(),
        'label' => "",
        'help' => "",
        'message1' => "",
        'message2' => "",
      ),
    ),
    'filepicker_user_view' => array(
      'arguments' => array(
        'view' => "",
        'form1' => array(),
        'form2' => array(),
        'form3' => array(),
      ),
    ),
    'filepicker_admin_view' => array(
      'arguments' => array(
        'view' => "",
        'form1' => array(),
        'form2' => array(),
        'form3' => array(),
      ),
    ),
    'filepicker_insert' => array(
      'arguments' => array(
        'file' => NULL,
        'public' => NULL,
        'form1' => array(),
        'form2' => array(),
      ),
    ),
    'filepicker_upload_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_user_file_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_user_config_admin_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_admin_file_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_user_search_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_group_search_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_quota_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_edit_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_groups_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_group_delete_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_file_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_groups_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_public_groups_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_group_files_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_public_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_search_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_settings_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_admin_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_list_admin' => array(
      'arguments' => array(
        'forms' => '',
        'message' => '',
        'pref' => '',
        'suff' => '',
        'label' => '',
      ),
    ),
    'filepicker_multitask_delete_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_multitask_groups_form' => array(
      'arguments' => array(
        'form' => array(),
      ),
    ),
    'filepicker_import_form' => array(
      'arguments' => array(
        'form' => NULL,
      ),
    ),
    'filepicker_import_dir_form' => array(
      'arguments' => array(
        'form' => NULL,
      ),
    ),
  );
}

// preprocess for filepicker.tpl.php
function template_preprocess_filepicker(&$variables) {
  global $language;
  if (module_exists('admin_menu')) {
    admin_menu_suppress();
  }

  $variables['head_title']  = (drupal_get_title() ? strip_tags(drupal_get_title()) : variable_get('site_name', 'Drupal'));
  $variables['styles'] = drupal_get_css();
  $variables['scripts'] = drupal_get_js();
  // fix jquery version thing in the iframe
  if (module_exists('jquery_update')) {
    jquery_update_preprocess_page($variables);
  }
  $variables['tabs'] = theme('menu_local_tasks');
  $variables['messages'] = filepicker_strip_messages(theme('status_messages'));
  $variables['language'] = $language;

}

// set up the iframe
function theme_filepicker_iframe($content, $file='', $public=FALSE) {

  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');
  if ($file) {
    global $user;
    $settings = array(
      'filepicker_iframe' => array(
        'isFCKeditor' => (module_exists('fckeditor') ? 'yes' : 'no' ),
        'isWysiwyg' => (module_exists('wysiwyg') ? 'yes' : 'no' ),
        'colorbox_enable' => (module_exists('colorbox') && variable_get('filepicker_colorbox_enable', 0)),
        'colorbox_iframe' => (filepicker_get_colorbox_perms()),
        'file_new_window' => variable_get('filepicker_use_new_window', 0)
      ),
    );
    drupal_add_js($settings, 'setting');
    drupal_add_js(FILEPICKER_PATH .'/filepicker_iframe.js');
  }
  return $content;
}

function theme_filepicker_list($header, $rows, $max, $message="", $pref="", $suff="", $label="", $cols = 1) {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  if ($rows) {
    $pager = theme('pager', NULL, $max);
    if ($pager) {
      $rows[] = array(array('data' => $pager, 'colspan' => $cols));
    }
    $output .= $pref . theme('table', $header, $rows) . $suff;
  }
  else {
    $output .= '<div class="messages">'. $message .'</div>';
  }
  $output .= ($label ? '</fieldset>' : '');
  return $output;

}

function theme_filepicker_stats($header, $rows, $pref="", $suff="", $label="") {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  $output .= $pref . theme('table', $header, $rows) . $suff;
  $output .= ($label ? '</fieldset>' : '');
  return $output;
}

function theme_filepicker_fullpage($file, $source, $link) {
  $output = '<div id="filep_page"><div id="filep_page_file">';
  $output .= '<a href="'. $source .'" alt="'. $file['file_title'] .'" target="_blank">';
  $output .= '<file src="'. $source .'" alt="'. $file['file_title'] .'" /></a></div>';
  $output .= ($link ? '<div><a href="#" onclick="history.back()">'. t('Return to page') .'</a></div>' : '');
  $output .= '</div>';
  return $output;
}

function theme_filepicker_quota_message($message1, $message2, $form, $label, $help) {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  $output .= ($message1 ? '<p class="messages">'. $message1 .'</p>' : '') ;
  $output .= ($help ? '<div class="filep_help">' . $help . '</div>' : '');
  $output .= $form;
  $output .= ($message2 ? '<p class="messages">'. $message2 .'</p>' : '') ;
  $output .= ($label ? '</fieldset>' : '');
  return $output;
}

function theme_filepicker_view($file, $filepath, $info) {
  $output = '<div id="filep_file_view">';
  $output .= '<div id="filep_file_view_name">' . t('Name') .": ". $file['file_name'] . '</div>';
  $output .= ($file['file_title'] ? '<div id="filep_file_view_title">'. t('Title') .": ". $file['file_title'] .'</div>' : '');
  $output .= '<div id="filep_file_view_info">' . t('Size') .": ". _filepicker_bkmg($info['file_size']) .'</div>';
  $output .= '</div>';
  return $output;
}

function theme_filepicker_file_edit_header($file) {
  $output = '<div class="filep_help">' . t('Edit details for %f', array('%f' => $file['file_name'])) . '</div>';
  return $output;
}

function theme_filepicker_quota($form, $message, $label) {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  $output .= ($message ? '<p class="messages">'. $message .'</p>' : '') ;
  $output .= $form;
  $output .= ($label ? '</fieldset>' : '');
  return $output;
}


function theme_filepicker_user_config($form, $label='', $help='', $message1='', $message2='') {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  $output .= ($help ? '<div class="filep_help">' . $help . '</div>' : '');
  $output .= ($message1 ? '<p class="messages">'. $message1 .'</p>' : '') ;
  $output .= $form;
  $output .= ($message2 ? '<p class="messages">'. $message2 .'</p>' : '') ;
  $output .= ($label ? '</fieldset>' : '');
  return $output;
}

function theme_filepicker_user_view($view, $form1='', $form2='', $form3='') {
  $output = "";
  $output .= $view;
  $output .= '<br />';
  $output .= ($form1 ? $form1 : '') ;
  $output .= '<br />';
  $output .= ($form2 ? $form2 : '') ;
  $output .= ($form3 ? $form3 : '') ;
  return $output;
}

function theme_filepicker_admin_view($view, $form1='', $form2='', $form3='') {
  $output = "";
  $output .= $view;
  $output .= '<br />';
  $output .= ($form1 ? $form1 : '') ;
  $output .= '<br />';
  $output .= ($form2 ? $form2 : '') ;
  $output .= ($form3 ? $form3 : '') ;
  return $output;
}

function theme_filepicker_insert($file='', $public=FALSE, $form1='', $form2='') {
  $output = "";
  if ($file) {
    $filepath = filepicker_get_file_path($file, ($public ? array('name' => $file['name'] , 'uid' => $file['uid']) : FALSE ));
    $output .= '<div class="filep_help">'. t('Choose the settings you want, place the cursor in the Body box above and Insert file.') .'</div>';
    $output .= '<div id="filep_file_view_name">' . t('Name') .": ". $file['file_name'] . '</div>';
    $output .= ($file['file_title'] ? '<div id="filep_file_view_title">'. t('Title') .": ". $file['file_title'] .'</div>' : '');
    $output .= $form1;
    $output .= $form2;
  }
  return $output;
}

function theme_filepicker_upload_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_user_file_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_user_config_admin_form($form) {
  $output = '';
  $form['submit']['#prefix'] = '<div class="container-inline">';
  $form['reset']['#suffix'] = '</div>';

  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_admin_file_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_user_search_form($form) {
  $output = '';
  $form['filepicker_currentuser']['#prefix'] = '<div id="filep_users_form" class="container-inline">';
  $form['filepicker_user_search_submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_group_search_form($form) {
  $output = '';
  $form['filepicker_currentgroup']['#prefix'] = '<div id="filep_groups_form" class="container-inline">';
  $form['filepicker_group_search_submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_quota_form($form) {
  $output = '';
  $form['filepicker_quota']['#prefix'] = '<div id="filep_quota_form" class="container-inline">';
  $form['submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_edit_form($form) {
  $output = '';
  $form['submit']['#prefix'] = '<div id="filep_controls">';
  $form['cancel']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_groups_form($form) {
  $output = '';
  $form['groupsave']['group_public_roles']['#prefix'] = '<div id="wrap-group-public-roles">';
  $form['groupsave']['group_public_roles']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_group_delete_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_file_form($form) {
  $output = '';
  if (isset($form['delete'])) {
    $form['insert']['#prefix'] = '<div id="filep_controls">';
    $form['delete']['#suffix'] = '</div>';
  }
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_groups_form($form) {
  $output = '';
  $form['gid']['#prefix'] = '<div id="filep_groups_form" class="container-inline">';
  $form['submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_public_groups_form($form) {
  $output = '';
  $form['gid']['#prefix'] = '<div id="filep_groups_form" class="container-inline">';
  $form['submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_group_files_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_public_form($form) {
  $output = '';
  $form['filepicker_list_public']['#prefix'] = '<div id="filep_list_form" class="container-inline">';
  $form['submit']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_search_form($form) {
  $output = '';
  $form['filepicker_list_search']['#prefix'] = '<div id="filep_search_form" class="container-inline">';
  $form['reset']['#suffix'] = '</div>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_settings_form($form) {
  $output = '';

  $jshide = ($form['filepicker_import']['filepicker_import_enabled']['#default_value'] ? '' : ' class="js-hide"');
  $form['filepicker_import']['filepicker_import_delete']['#prefix'] = '<div id="wrap-filepicker-import"'. $jshide .'>';
  $form['filepicker_import']['filepicker_import_max']['#suffix'] = '</div>';

  $jshide = ($form['filepicker_groups']['filepicker_groups_enabled']['#default_value'] ? '' : ' class="js-hide"');
  $form['filepicker_groups']['filepicker_public_enabled']['#prefix'] = '<div id="wrap-filepicker-groups"'. $jshide .'>';
  $form['filepicker_groups']['filepicker_groups_in_upload_enabled']['#suffix'] = '</div>';

  $jshide = ($form['filepicker_progress']['filepicker_upload_progress_enabled']['#default_value'] ? '' : ' class="js-hide"');
  $form['filepicker_progress']['filepicker_upload_progress_delay']['#prefix'] = '<div id="wrap-filepicker-upload-progress"'. $jshide .'>';
  if (version_compare(phpversion(), FILEPICKER_UPLOAD_STATUS_MIN_PHP) >= 0 && extension_loaded('uploadprogress')) {
    $form['filepicker_progress']['filepicker_uploadprogress']['#suffix'] = '</div>';
  }
  else {
    $form['filepicker_progress']['filepicker_upload_progress_message']['#suffix'] = '</div>';
  }

  $jshide = ($form['filepicker_quotas']['filepicker_quota_byrole']['#default_value'] ? '' : ' class="js-hide"');
  $form['filepicker_quotas']['filepicker_quota_role']['#prefix'] = '<div id="wrap_filepicker_quota_role"'. $jshide .'>';
  $form['filepicker_quotas']['filepicker_quota_role']['#suffix'] = '</div>';

  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_admin_form($form) {
  $src = $form['options']['src']['#value'];
  $cols = $form['options']['cols']['#value'];
  $public = $form['options']['public']['#value'];
  $form['options']['#prefix'] = '<div class="container-inline">';
  $form['options']['#suffix'] = '</div>';
  // tablesort
  if ($public && $src == 'admin') {
    $header = array(
      theme('table_select_header_cell'),
      array('data' => t('Name'), 'field' => 'i.file_name'),
      array('data' => t('Title'), 'field' => 'i.file_title'),
      array('data' => t('User'), 'field' => 'n.name'),
      array('data' => t('Date'), 'field' => 'i.file_date'),
      array('data' => t('Actions'), 'colspan' => 2),
    );
  }
  else {
    $header = array(
      ($public ? array() : theme('table_select_header_cell')),
      array('data' => t('Name'), 'field' => 'i.file_name'),
      array('data' => t('Title'), 'field' => 'i.file_title'),
      array('data' => t('Date'), 'field' => 'i.file_date'),
      array('data' => t('Actions'), 'colspan' => 2),
    );
  }

  $output = drupal_render($form['options']);

  if (isset($form['file_name']) && is_array($form['file_name'])) {
    foreach (element_children($form['file_name']) as $key) {
      if ($public && $src == 'admin') {
        $rows[] = array(
          drupal_render($form['files'][$key]),
          drupal_render($form['file_name'][$key]),
          drupal_render($form['file_title'][$key]),
          drupal_render($form['file_list'][$key]),
          drupal_render($form['file_date'][$key]),
          drupal_render($form['file_edit'][$key]),
          drupal_render($form['file_delete'][$key]),
        );
      }
      else {
        if ($public) {
          $rows[] = array(
            drupal_render($form['file_name'][$key]),
            drupal_render($form['file_title'][$key]),
            drupal_render($form['file_date'][$key]),
            drupal_render($form['file_edit'][$key]),
            drupal_render($form['file_delete'][$key]),
          );
        }
        else {
          $rows[] = array(
            drupal_render($form['files'][$key]),
            drupal_render($form['file_name'][$key]),
            drupal_render($form['file_title'][$key]),
            drupal_render($form['file_date'][$key]),
            drupal_render($form['file_edit'][$key]),
            drupal_render($form['file_delete'][$key]),
          );
        }
      }
    }
  }
  else {
    $rows[] = array(array('data' => t('No files available.')));
    $header = array();
  }
  if ($form['pager']['#value']) {
    $pager = drupal_render($form['pager']);
    $rows[] = array(array('data' => $pager, 'colspan' => $cols+1));
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_list_admin($forms='', $message="", $pref="", $suff="", $label="") {
  $output = ($label ? '<fieldset><legend>'. $label .'</legend>' : '');
  if ($forms) {
    $output .= $pref;
    $output .= $forms['list_search'];
    $output .= $forms['list_groups'];
    $output .= $forms['list_public'];
    $output .= $forms['list_public_groups'];
    $output .= $forms['list_admin'];
    $output .= $suff;
  }
  else {
    $output .= '<div class="messages">'. $message .'</div>';
  }
  $output .= ($label ? '</fieldset>' : '');
  return $output;
}

function theme_filepicker_multitask_delete_form($form) {
  $output = '';
  $count = $form['countnids']['#value'];
  $output .= '<p>'. t('You have selected %c to be deleted', array('%c' => format_plural( $count, '1 file', '@count files'))) . '</p>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_multitask_groups_form($form) {
  $output = '';
  $count = $form['countnids']['#value'];
  $output .= '<p>'. t('You have selected %c to be grouped', array('%c' => format_plural( $count, '1 file', '@count files'))) . '</p>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_import_form($form) {
  $output = '';
  $markup = $form['total']['#value'];
  $form['total']['#value'] = '<p>' . $markup . '</p>';
  $output .= drupal_render($form);
  return $output;
}

function theme_filepicker_import_dir_form($form) {
  $output = '';
  $output .= drupal_render($form);
  return $output;
}
