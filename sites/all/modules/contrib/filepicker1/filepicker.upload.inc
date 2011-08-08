<?php

/**
 * @file
 * upload functions
 */

/**
 * Menu callback; presents the upload form for filepicker
 */
// iframe
function filepicker_upload() {
  variable_del('filepicker_advanced_browser_pagestart');
  if (variable_get('filepicker_upload_progress_enabled', 1)) {
    $content = filepicker_upload_progress_get_script(variable_get('filepicker_upload_progress_delay', 0));
  }
  $content .= filepicker_quota_ok('iframe', FALSE, '', t('Upload files. You can give them a title and description'));
  return theme('filepicker_iframe', $content);
}
// account
function filepicker_user_upload() {
  global $user;
  variable_del('filepicker_advanced_browser_pagestart');
  if (variable_get('filepicker_upload_progress_enabled', 1)) {
    $content = filepicker_upload_progress_get_script(variable_get('filepicker_upload_progress_delay', 0));
  }
  $content .= filepicker_quota_ok('user', $user, '', t('Upload files. You can give them a Link text'));
  return $content;
}

function filepicker_upload_form(&$form_state, $account=FALSE, $admin = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $form['#attributes']['enctype'] = 'multipart/form-data';
  if (variable_get('filepicker_upload_progress_enabled', 1) && variable_get('filepicker_uploadprogress_server', '')) {
    $form[FILEPICKER_UPLOAD_ID] = array(
      '#type' => 'hidden',
      '#value' => uniqid(),
      '#weight' => -50,
    );
  }
  $max_filesize = ini_get('upload_max_filesize');
  $form['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('File'),
    '#description' => t('Browse your computer for a file, Max. %max', array('%max' => $max_filesize)),
    '#required' => TRUE,
    '#value' => 1,
    '#size' => 40,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text'),
    '#description' => t('The text to use for a link. The default is the filename'),
  );
  // groups
  if (variable_get('filepicker_groups_enabled', 1) && variable_get('filepicker_groups_in_upload_enabled', 1)) {
    $grouplist = filepicker_get_groups( ($admin ? $user : FALSE));
    if ($grouplist) {
      $form['grouplist'] = array(
        '#type' => 'checkboxes',
        '#options' => $grouplist,
        '#title' => t('Your Groups'),
        '#description' => t('Select a group to add your file to.'),
      );
    }
  }

  if ($account) {
    $form['account'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
    );
  }
  if ($admin) {
    $form['admin'] = array(
      '#type' => 'value',
      '#value' => 1,
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Upload'),
  );
  if (variable_get('filepicker_upload_progress_enabled', 1)) {
    $form['#suffix'] = filepicker_upload_progress_busy();
  }
  return $form;
}

/**
 * Validate form
 */
function filepicker_upload_form_validate($form, &$form_state) {
  foreach ($form_state['values'] as $name => $value) {
    switch ($name) {
      case 'file_upload':
        if (empty($_FILES['files']['name']['file_upload'])) {
          form_set_error($name, t(' file upload field is required.'));
        }
        elseif (!isset($_FILES['files']['tmp_name']['file_upload']) || !file_exists($_FILES['files']['tmp_name']['file_upload'])) {
          form_set_error($name, t('Error while uploading file.'));
        }
        elseif (!filepicker_get_uploaded_file_extension('file_upload')) {
          form_set_error($name, t('Illegal file.'));
        }
        break;
    }
  }
}

/**
 * Submit form
 */
function filepicker_upload_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Upload')) {
    if ( isset($form_state['values']['account']) && isset($form_state['values']['admin'])) {
      $user = user_load(array('uid' => $form_state['values']['account']));
    }
    else {
      global $user;
    }
    $destdir = filepicker_get_path(FALSE, (isset($form_state['values']['admin']) ? array('name' => $user->name, 'uid' => $user->uid ) : TRUE));

    if (file_check_directory($destdir, TRUE)) {
      // clear out the noisy 'created' messages
      drupal_get_messages('status', TRUE);
      // Add DIRECTORY_SEPARATORS here because drupals' functions remove trailing slashes
      $destdir .= DIRECTORY_SEPARATOR;
      $destination = $destdir;
      $filemoved = filepicker_copy_uploaded_file($destination, 'file_upload');
      if ($filemoved) {
        $file = filepicker_get_uploaded_file_name($destination, 'file_upload');
        $title = htmlspecialchars($form_state['values']['title']);
        $nextfileid = filepicker_insert_file($user->uid, $file, $title);
        if ($nextfileid) {
          if ( is_array($form_state['values']['grouplist']) && variable_get('filepicker_groups_enabled', 1) && variable_get('filepicker_groups_in_upload_enabled', 1) ) {
            $result = db_query("SELECT file_id FROM {filepicker} WHERE uid = '%d' AND file_name = '%s'", array($user->uid, $file));
            $row = db_fetch_array($result);
            $record['file_id']  = $row['file_id'];
            foreach ($form_state['values']['grouplist'] AS $gid) {
              $record['gid'] = $gid;
              filepicker_insert_group_file($record);
            }
          }
          drupal_set_message(t('File was successfully uploaded.'));
          if (isset($form_state['values']['admin'])) {
            $outpath = FILEPICKER_ADMIN_PATH .'/files/user/'. $user->uid .'/list';
          }
          elseif (isset($form_state['values']['account'])) {
            $outpath = 'user/'. $user->uid .'/filepicker/files/list';
          }
          else {
            $outpath = 'filepicker/list/'. $nextfileid;
          }
          // external functions
          #module_invoke_all('filepicker_upload_extra', $nextfileid);
          drupal_goto($outpath);
        }
        else {
          file_delete($destdir . $file);
          drupal_set_message(t('Error while saving information to database for uploaded file.'), 'error');
        }
      }
      else {
        drupal_set_message(t('Error while moving uploaded file to its destination.'), 'error');
      }
      file_delete($destdir . $file);
    }
    else {
      drupal_set_message(t('Unable to create a directory structure for your files.'), 'error');
    }
  }
  if (isset($form_state['values']['admin'])) {
    $outpath = FILEPICKER_ADMIN_PATH .'/files';
  }
  elseif (isset($form_state['values']['account'])) {
    $outpath = 'user/'. $user->uid .'/filepicker';
  }
  else {
    $outpath = 'filepicker';
  }
  drupal_goto($outpath);
}


function filepicker_copy_uploaded_file(&$destination, $name) {
  $source = $_FILES['files']['tmp_name'][$name];

  if (file_copy($source, $destination, FILE_EXISTS_RENAME)) {
    // Fix bug in drupal's file_copy function which uses '/' instead of
    // DIRECTORY_SEPARATOR for making directories. This causes problems on
    // Windows machines.
    $source = str_replace('/', DIRECTORY_SEPARATOR, $source);

    $file = filepicker_get_uploaded_file_name($destination, $name);
    $destination = $destination . $file;
    return @rename($source, $destination);
  }

  return FALSE;
}

function filepicker_get_uploaded_file_extension($name) {
  $filename = $_FILES['files']['name'][$name];
  return filepicker_validate_is_file($filename);
}

function filepicker_get_uploaded_file_name($destination, $name) {
  $fileext = filepicker_get_uploaded_file_extension($name);

  if (FALSE !== strpos($_FILES['files']['name'][$name], '.')) {
    $filename = drupal_substr($_FILES['files']['name'][$name], 0, strrpos($_FILES['files']['name'][$name], '.'));
  }
  else {
    $filename = $_FILES['files']['name'][$name];
  }

  $file = $filename .'.'. $fileext;
  $i = 0;
  while (file_exists($destination . $file)) {
    $i++;
    $file = $filename .'_'. $i .'.'. $fileext;
  }
  return $file;
}

function filepicker_upload_progress_get_script($delay) {

  $message = variable_get('filepicker_upload_progress_message', t('Processing form... please wait.'));
  if (variable_get('filepicker_uploadprogress_server', '')) {
    // Immediately disable devel shutdown functions so that it doesn't botch our
    // JSON output.
    $GLOBALS['devel_shutdown'] = FALSE;
    $settings = array(
      'filepicker_upload_progress' => array(
        'callback' => 'http://' . $_SERVER['HTTP_HOST'] . url('filepicker/progress'),
        'interval' => variable_get('filepicker_uploadprogress_interval', 1),
        'name' => FILEPICKER_UPLOAD_ID,
        'delay' => $delay,
        'initmessage' => $message,
        'cancelmessage' => t('Cancel'),
      ),
    );
  }
  else {
    $settings = array(
      'filepicker_upload_progress' => array(
        'callback' => '',
        'interval' => '',
        'name' => '',
        'delay' => $delay,
        'initmessage' => $message,
        'cancelmessage' => t('Cancel'),
      ),
    );
  }

  drupal_add_js(FILEPICKER_PATH .'/filepicker_upload.js');
  drupal_add_js($settings, 'setting');
}

function filepicker_upload_progress_busy() {
  return '<div id="filepicker-sending" style="display: none;"></div>';
}

