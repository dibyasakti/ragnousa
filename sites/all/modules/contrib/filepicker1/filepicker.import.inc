<?php

/**
 * @file
 * manage batch imports.
 */

/**
 * Function to check the import folder.
 * @param $account
 *   Optional. user override
 * @return
 *   Returns the number of files.
 */
function filepicker_import_dir_check($checkonly = FALSE) {
  $importok = TRUE;
  if (! $importdir = variable_get('filepicker_import_dir', '')) {
    $importok = FALSE;
    $errmsg = t('Import Directory not set');
    $errstatus = 'status';
  }
  elseif (variable_get('filepicker_import_delete', 0)) {
    if (! file_check_directory($importdir, TRUE)) {
      $importok = FALSE;
      $errmsg = t('Directory not found or not writable');
      $errstatus = 'error';
    }
  }
  elseif (! file_exists($importdir)) {
    $importok = FALSE;
    $errmsg = t('Directory not found or not readable');
    $errstatus = 'error';
  }
  if (! $importok) {
    drupal_set_message($errmsg, $errstatus);
    return FALSE;
  }

  if ($checkonly) {
    return TRUE;
  }

  // clear out the noisy 'created' messages
  drupal_get_messages('status', TRUE);
  $importlist = file_scan_directory($importdir, ".*", array('.', '..', 'CVS'), 0, FALSE);
  $checked_importlist = array();
  $bad_importlist = array();
  if (count($importlist)) {
    foreach ($importlist AS $k => $v) {
      $file = $importlist[$k]->basename;
      if (filepicker_validate_is_file($file)) {
        $checked_importlist[] = $file;
      }
    }
  }
  else {
    drupal_set_message(t('No files to import.'), 'warning');
  }
  return (count($checked_importlist) > 0 ? $checked_importlist : 0);
}

/**
 * Function to display the file import form.
 *
 * @param $total
 *   Required. total number of files being imported.
 * @param $account
 *   Optional. user override
 * @param $admin
 *   Optional. admin switch
 * @return
 *   Returns the file form.
 */
function filepicker_import_form(&$form_state, $total, $account=FALSE, $admin = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  // provide checkbox list of groups if any
  // default watermark
  $form['total'] = array(
    '#type' => 'markup',
    '#value' => t('!total files found in the filepicker import folder.<br />Selected user is %user', array('!total' => $total, '%user' => $user->name )),
  );

  // groups
  if (variable_get('filepicker_groups_enabled', 1) && variable_get('filepicker_groups_in_upload_enabled', 1)) {
    $grouplist = filepicker_get_groups( ($admin ? $user : FALSE));
    if ($grouplist) {
      $form['grouplist'] = array(
        '#type' => 'checkboxes',
        '#options' => $grouplist,
        '#title' => t('Your Groups'),
        '#description' => t('Select a group to add this import to.'),
      );
    }
  }

  if ($admin) {
    $form['admin'] = array(
      '#type' => 'value',
      '#value' => 1,
    );
  }
  if ($account) {
    $form['account'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;

}

/**
 * Submit form
 */
function filepicker_import_form_submit($form, &$form_state) {
  $op = isset($form_state['values']['op']) ? $form_state['values']['op']: '';
  if ($op == t('Import')) {
    if ( isset($form_state['values']['account']) && isset($form_state['values']['admin'])) {
      $user = user_load(array('uid' => $form_state['values']['account']));
    }
    else {
      global $user;
    }

    $destdir = filepicker_get_path(FALSE, (isset($form_state['values']['admin']) ? array('name' => $user->name, 'uid' => $user->uid ) : TRUE));
    $sourcedir = variable_get('filepicker_import_dir', '');

    if (file_check_directory($destdir, TRUE)
      && $selected = filepicker_import_dir_check()
      ) {
      // clear out the noisy 'created' messages
      drupal_get_messages('status', TRUE);
      // Add DIRECTORY_SEPARATORS here because drupals' functions remove trailing slashes
      $options['destdir'] = $destdir . DIRECTORY_SEPARATOR;
      $options['sourcedir'] = $sourcedir;

      $batch = array(
        'title' => t('Importing files'),
        'operations' => array(
          array('filepicker_import_batch', array($form_state, $selected, $options, $user)),
        ),
        'finished' => 'filepicker_import_finished',
        'file' =>  drupal_get_path('module', 'filepicker') ."/filepicker.import.inc",
        'progress_message' => t('Processed @current out of @total.'),
      );
      batch_set($batch);
      // batch_process();
    }
    else {
      drupal_set_message(t('Unable to import.'), 'error');
    }
  }
}

function filepicker_import_batch($form_state, $selected, $options, $account, &$context) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($selected);
    $context['sandbox']['files'] = $selected;
  }
  // Process files by groups of 5.
  $max = variable_get('filepicker_import_max', 5);
  $count = min($max, count($context['sandbox']['files']));
  for ($i = 0; $i < $count; $i++) {
    $index = array_shift($context['sandbox']['files']);

    // Check the file is OK
    $filename = $index;
    $source_filepath = file_check_location($options['sourcedir'] . DIRECTORY_SEPARATOR . $filename, $options['sourcedir']);
    if ($source_filepath &&  filepicker_validate_is_file($source_filepath)) {
      $source = $source_filepath;
      $file = $filename;

      // copy original
      if (file_copy($source, $options['destdir'], FILE_EXISTS_RENAME)) {
        $file = basename($source);
        $orig = $options['destdir'] . $file;

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
          // delete
          if (variable_get('filepicker_import_delete', 0)) {
            file_delete($source_filepath);
          }
        }
        else {
          file_delete($options['destdir'] . $file);
          $_SESSION['filepicker_import_status'] = t('Error while saving information to database for imported file %im.', array('%im' => $file));
        }
      }
      else {
        $_SESSION['filepicker_import_status'] = t('Could not copy to original: %file', array('%file' => $source_filepath));
      }
    }
    else {
      $_SESSION['filepicker_import_status'] = t('Invalid file: %file', array('%file' => $source_filepath));
    }
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['results'][] = $source_filepath;
    if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
      $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    }
    else {
      $context['finished'] = 1;
    }
  }
}

function filepicker_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One file processed.', '@count files processed.');
    variable_del('filepicker_import_dir');
  }
  else {
    $message = t('Finished with an error.');
  }
  $_SESSION['filepicker_import_status'] = $message;
}

/**
 * Function to display the import folder form
 *
 * @return
 *   Returns the import folder form.
 */
function filepicker_import_dir_form(&$form_state) {
  $readstate = t('readable');
  if (variable_get('filepicker_import_delete', 0)) {
    $readstate = t('writeable');
  }

  $form['filepicker_import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filepicker Import Folder'),
    '#description' => t('Path of the import folder, relative to the Drupal root or an absolute path.<br />This is where you upload files to, via FTP or rsync.<br />This folder must be !readstate by the webserver.', array('!readstate' => $readstate)),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['filepicker_import']['filepicker_import_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Import Folder'),
    '#size' => 55,
    '#maxlength' => 100,
    '#required' => FALSE,
    '#default_value' => variable_get('filepicker_import_dir', ''),
  );
  $form['filepicker_import']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['filepicker_import']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  return $form;
}

/**
 * Validate form
 */
function filepicker_import_dir_form_validate($form, &$form_state) {
  $importdir = $form_state['values']['filepicker_import_dir'];
  if ($form_state['values']['op'] == t('Save')) {
    if (variable_get('filepicker_import_delete', 0)) {
      if (! file_check_directory($importdir, TRUE)) {
        form_set_error('filepicker_import_dir', t('Directory not found or not writable'));
      }
    }
    elseif (! file_exists($importdir)) {
      form_set_error('filepicker_import_dir', t('Directory not found or not readable'));
    }
  }
}

/**
 * Submit form
 */
function filepicker_import_dir_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
    variable_set('filepicker_import_dir', $form_state['values']['filepicker_import_dir']);
  }
  else {
    variable_del('filepicker_import_dir');
  }
}
