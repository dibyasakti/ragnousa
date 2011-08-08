<?php

/**
 * @file
 * filepicker functions.
 */

/**
 * Menu local task; presents the list and select pages for filepicker
 */
function filepicker_list($file_id=0) {
  if ( $file_id ) {
    return filepicker_file_select($file_id);
  }
  else {
    return theme('filepicker_iframe', _filepicker_list_admin());
  }
}

function filepicker_list_public($file_id=0) {
  if ( $file_id ) {
    return filepicker_file_select($file_id, FALSE, TRUE);
  }
  else {
    #return theme('filepicker_iframe', _filepicker_list_public());
    return theme('filepicker_iframe', _filepicker_list_admin('iframe', FALSE, TRUE));
  }
}

function filepicker_file_select($file_id, $showgroup=TRUE, $public = FALSE, $account = FALSE) {
  global $base_url;
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $file = _filepicker_get_file($file_id, ($public ? FALSE : TRUE));
  if ($file) {
    $form1 = '';
    if ($user->uid == $file['uid'] || $public) {
      if (variable_get('filepicker_use_full_url', 0)) {
        $filepath = $base_url . DIRECTORY_SEPARATOR . file_directory_path() . DIRECTORY_SEPARATOR . FILEPICKER_FILES_DIR . DIRECTORY_SEPARATOR . $file['uid'] . DIRECTORY_SEPARATOR . $file['file_name'];
      }
      else {
        $filepath = filepicker_get_file_path($file, ($public ? array('name' => $file['name'] , 'uid' => $file['uid']) : FALSE ));
      }
      $form1 = drupal_get_form('filepicker_file_form', $file, $filepath, $public);
    }

    // groups
    $form2 = '';
    if (_filepicker_has_groups() && $showgroup) {
      $form2 = drupal_get_form('filepicker_group_files_form', $file['file_id']);
    }

    $content = theme('filepicker_insert', $file, $public, $form1, $form2);

  }
  else {
    drupal_set_message(t('File not found.'), 'error');
    $content = '';
  }

  return theme('filepicker_iframe', $content, $file, $public);
}

/**
 * Function to display the file insertion form
 *
 * @param $file_id
 *   The id of the file to be inserted.
 * @param $public
 *   Optional, ensures that public files cannot be edited.
 * @return
 *   Returns the file form.
 */
function filepicker_file_form(&$form_state, $file, $filepath, $public = FALSE) {
  global $user;
  $form['insert'] = array(
    '#type' => 'button',
    '#value' => t('Insert file'),
    '#attributes' => array('onclick' => 'filepickerInsert(this); return false;')
  );
  if (! $public) {
    $form['edit'] = array(
      '#type' => 'submit',
      '#value' => t('Edit file'),
      '#submit' => array('filepicker_file_form_edit'),
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete file'),
      '#submit' => array('filepicker_file_form_delete'),
    );
  }
  $form['file_id'] = array(
    '#type' => 'value',
    '#value' => $file['file_id'],
  );
  // for js to pick up
  $form['file_title'] = array(
    '#type' => 'hidden',
    '#value' => $file['file_title'],
  );
  $form['file_path'] = array(
    '#type' => 'hidden',
    '#value' => $filepath,
  );
  $form['file_name'] = array(
    '#type' => 'hidden',
    '#value' => $file['file_name'],
  );

  return $form;
}

/**
 * Submit form functions
 */
function filepicker_file_form_delete($form, &$form_state) {
  filepicker_file_delete($form_state['values']['file_id']);
}

function filepicker_file_form_edit($form, &$form_state) {
  drupal_goto('filepicker/edit/'. $form_state['values']['file_id']);
}

function filepicker_file_delete($file_id, $account=FALSE, $src='iframe') {
  if ($account) {
    $user = $account;
    $userdir = array('name' => $user->name, 'uid' => $user->uid);
  }
  else {
    global $user;
    $userdir = TRUE;
  }
  if ($src == 'account') {
    $outpath = 'user/'. $user->uid .'/filepicker/files/list';
  }
  elseif ($src == 'admin') {
    $outpath = FILEPICKER_ADMIN_PATH .'/files/user/'. $user->uid .'/list';
  }
  else {
    $outpath ='filepicker/list';
  }
  _filepicker_file_delete($file_id, $account, $src);
  drupal_goto($outpath);
}

function _filepicker_file_delete($file_id, $account=FALSE, $src='iframe', $suppress = FALSE) {
  if ($account) {
    $user = $account;
    $userdir = array('name' => $user->name, 'uid' => $user->uid);
  }
  else {
    global $user;
    $userdir = TRUE;
  }
  $file = _filepicker_get_file($file_id, ($src=='admin' ? FALSE : TRUE), ($account ? $user : FALSE));
  if ($file) {
    $destination = filepicker_get_path(FALSE, $userdir);
    file_delete($destination . $file['file_name']);
    if (db_query("DELETE FROM {filepicker} WHERE uid = %d AND file_id = %d", array($user->uid, $file_id))) {
      // groups entries
      db_query("DELETE FROM {filepicker_group_files} WHERE file_id = %d", array($file_id));
      if (! $suppress) {
        drupal_set_message(t('File was successfully deleted'));
      }
    }
    else {
      drupal_set_message(t('Error while trying to delete your file from database.'), 'error');
    }
  }
  else {
    drupal_set_message(t('File not found.'), 'error');
  }
  return;
}

/**
 * some common utilities
 */
function filepicker_get_path($url = FALSE, $userdir = FALSE) {
  global $user, $base_url;

  $dirsep = !$url ? DIRECTORY_SEPARATOR : '/';

  if (!$url) {
    $path = str_replace('/', DIRECTORY_SEPARATOR, getcwd());
  }
  elseif (variable_get('filepicker_use_full_url', 0)) {
    $path = $base_url;
  }
  else {
    $path = base_path();
    $path = preg_replace("/\/$/", "", $path);
  }

  $path .= $dirsep . file_directory_path() . $dirsep . FILEPICKER_FILES_DIR . $dirsep;

  if ($userdir) {
    $useruid = !is_array($userdir) ? $user->uid : $userdir['uid'];
    $path .= $useruid . $dirsep;
  }

  return $path;
}

function filepicker_get_file_path($file, $public = FALSE) {
  $filebasedir = filepicker_get_path(FALSE, (is_array($public) ? $public : TRUE));
  $filepath = '';
  if (file_exists($filebasedir . $file['file_name'])) {
    $filepath = filepicker_get_path(TRUE, (is_array($public) ? $public : TRUE)) . $file['file_name'];
  }
  return $filepath;
}

// There is not need to inform users, that directory structure has been created
// and show them all paths... So lets strip these messages if there are any.
function filepicker_strip_messages($msg) {
  if ($msg) {
    $dirsep = (DIRECTORY_SEPARATOR == '\\') ? '\\\\' : '\/';
    $pattern = '/<li>.*'. $dirsep .'filepicker'. $dirsep .'.*<\/li>/i';
    $msg = preg_replace($pattern, '', $msg);
  }
  return $msg;
}

/**
 * list of files with bulk operations
 */
function filepicker_list_admin_form(&$form_state, $src="iframe", $account=FALSE, $public=FALSE, $range=1) {

  global $base_url;
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  // paths
  if ($src == 'iframe') {
    $path = '';
    $editpath   = "filepicker/edit/";
    $deletepath = "filepicker/delete/";
    $filepath    = 'filepicker/list/';
    if ($public) {
      $filepath    = 'filepicker/list_public/';
    }
  }
  elseif ($src == 'admin') {
    $path = FILEPICKER_ADMIN_PATH;
    $editpath   = $path .'/files/user/'. $user->uid .'/edit/';
    $deletepath = $path .'/files/user/'. $user->uid .'/delete/';
    $filepath    = $path .'/files/user/'. $user->uid .'/list/';
    $returnpath = 'a-'. $user->uid;
  }
  else {
    $path = 'user/'. $user->uid . '/filepicker';
    $editpath   = $path .'/files/edit/';
    $deletepath = $path .'/files/delete/';
    $filepath    = $path .'/files/list/';
    $returnpath = 'u-'. $user->uid;
  }

  // if there are groups
  if (variable_get('filepicker_groups_enabled', 1)) {
    $gid = 0;
    if (! $public) {
      if (_filepicker_has_groups( ($src == 'admin' ? $user : FALSE) ) && filepicker_has_grouplist(($src == 'admin' ? $user : FALSE))) {
        $gids = filepicker_get_user_group_state(1, ($src == 'admin' ? $user : FALSE));
        $gid = $gids[0];
        if ($account) {
          $gid = variable_get('filepicker_currentgroup', 0);
        }
      }
    }
    elseif ($src == 'admin' && _filepicker_has_public_groups($user, TRUE)) {
      $gid = variable_get('filepicker_public_currentgroup', 0);
    }
  }

  // tablesort
  if ($public && $src == 'admin') {
    $header = array(
      array(),
      array('data' => t('Name'), 'field' => 'i.file_name'),
      array('data' => t('Title'), 'field' => 'i.file_title'),
      array('data' => t('User'), 'field' => 'n.name'),
      array('data' => t('Date'), 'field' => 'i.file_date'),
      array('data' => t('Actions'), 'colspan' => 2),
    );
    $cols = 5;
  }
  else {
    if ($public) {
      $header = array(
        array('data' => t('Name'), 'field' => 'i.file_name'),
        array('data' => t('Title'), 'field' => 'i.file_title'),
        array('data' => t('Date'), 'field' => 'i.file_date'),
        array('data' => t('Actions'), 'colspan' => 2),
      );
    }
    else {
      $header = array(
        array(),
        array('data' => t('Name'), 'field' => 'i.file_name'),
        array('data' => t('Title'), 'field' => 'i.file_title'),
        array('data' => t('Date'), 'field' => 'i.file_date'),
        array('data' => t('Actions'), 'colspan' => 2),
      );
    }
    $cols = 4;
  }

  $use_icons = variable_get('filepicker_use_icons', 1);
  if ($src == 'admin') {
    $how_many = variable_get('filepicker_rows_per_page', 25);
  }
  else {
    $how_many = (isset($user->filepicker_rows_per_page) ? $user->filepicker_rows_per_page : variable_get('filepicker_rows_per_page', 25));
  }
  $searchs = (isset($user->filepicker_list_search) ? $user->filepicker_list_search : '');
  $searchs = trim($searchs);
  $sarr = '';
  $searchsql = '';
  if ($searchs) {
    $xarr = _filepicker_search_opts($searchs);
    $searchsql = $xarr[0];
    $sarr = $xarr[1];
  }
  if ($public && $src == 'admin') {
  #if ($src == 'admin') {
    if ($range == 1) {
      $sql = "SELECT i.file_id, i.uid, i.file_name, i.file_title, i.file_date, n.name
        FROM {filepicker} i, {users} n, {filepicker_user_groups} u, {filepicker_group_files} g
        WHERE i.uid=n.uid AND u.public=1 AND g.file_id=i.file_id AND u.gid=g.gid";
      if ($searchsql) {
        $sql .= $searchsql;
      }
      if ($gid) {
        $sql .= " AND u.gid = %d";
        $garr = array($gid);
      }
      $sql .= tablesort_sql($header);
      $label = t('List All Public Files');
    }
    elseif ($range == 2) {
      $sql = "SELECT i.file_id, i.uid, i.file_name, i.file_title, i.file_date, n.name
        FROM {filepicker} i, {users} n, {filepicker_user_groups} u, {filepicker_group_files} g
        WHERE i.uid=n.uid AND u.public=0 AND g.file_id=i.file_id AND u.gid=g.gid";
      if ($searchsql) {
        $sql .= $searchsql;
      }
      $sql .= tablesort_sql($header);
      $label = t('List All Private Files');
    }
    else {
      $sql = "SELECT DISTINCT i.file_id, i.uid, i.file_name, i.file_title,i.file_date, n.name
        FROM {filepicker} i, {users} n
        WHERE i.uid = n.uid";
      if ($searchsql) {
        $sql .= $searchsql;
      }
      $sql .= tablesort_sql($header);
    }
    if (is_array($sarr) || is_array($garr)) {
      $rarr = array();
      if (is_array($sarr)) {
        $rarr = $sarr;
      }
      if (is_array($garr)) {
        $rarr = array_merge($rarr, $garr);
      }
      $result = pager_query($sql, $how_many, 0, NULL, $rarr);
    }
    else {
      $result = pager_query($sql, $how_many, 0, NULL);
    }
  }
  else {
    // filter by selected group
    if ($gid) {
      $sql = "SELECT i.file_id, i.uid, i.file_name, i.file_title, i.file_date
        FROM {filepicker} i, {filepicker_group_files} g
        WHERE i.uid=%d AND i.file_id=g.file_id AND g.gid=%d";
      if ($searchsql) {
        $sql .= $searchsql;
      }
      $sql .= tablesort_sql($header);
      if ($searchsql) {
        $rarr = array_merge(array($user->uid, $gid), $sarr);
      }
      else {
        $rarr = array($user->uid, $gid);
      }
    }
    else {
      if ($public) {
        $sql = "SELECT i.file_id, i.uid, i.file_name, i.file_title, i.file_date, n.name
          FROM {filepicker} i, {users} n, {filepicker_user_groups} u, {filepicker_group_files} g
          WHERE i.uid=n.uid AND u.public=1 AND g.file_id=i.file_id AND u.gid=g.gid";
      }
      else {
        $sql = "SELECT i.file_id, i.uid, i.file_name, i.file_title, i.file_date
          FROM {filepicker} i
          WHERE i.uid=%d";

      }
      if ($searchsql) {
        $sql .= $searchsql;
      }

      $sql .= tablesort_sql($header);
      if ($searchsql) {
        $rarr = array_merge(array($user->uid), $sarr);
      }
      else {
        $rarr = array($user->uid);
      }
    }
    $result = pager_query($sql, $how_many, 0, NULL, $rarr);
  }

  if ($admin || ! $public) {
    // bulk ops form
    $form['options'] = array(
      '#type' => 'fieldset',
      '#title' => t('Bulk operations'),
    );
    if ($src == 'admin' && ! $account) {
      $op_opts = array('delete' => t('Delete'));
    }
    else {
      $op_opts = array('delete' => t('Delete'), 'groups' => t('Groups'));
    }
    $form['options']['operation'] = array(
      '#type' => 'select',
      '#options' => $op_opts,
      '#default_value' => 'delete',
    );
    $form['options']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );
  }

  $form['options']['src'] = array(
    '#type' => 'value',
    '#value' => $src,
  );
  $form['options']['public'] = array(
    '#type' => 'value',
    '#value' => $public,
  );
  $form['options']['path'] = array(
    '#type' => 'value',
    '#value' => $path,
  );
  $rowct = 0;
  while ($row = db_fetch_array($result)) {
    // file_id file_name  file_title
    $file_name = check_plain($row['file_name']);
    $file_id = $row['file_id'];
    $filelink = l($file_name, $filepath . $file_id);
    $file_date = format_date($row['file_date'], variable_get('filepicker_dateformat_default', 'medium'));

    if ($public && $src == 'admin') {
      $editpath   = $path .'/files/user/'. $row['uid'] .'/edit/';
      $deletepath = $path .'/files/user/'. $row['uid'] .'/delete/';
      $listpath   = $path .'/files/user/'. $row['uid'] .'/list';
      $returnpath = 'a';
      $editlink = ($use_icons ? _filepicker_get_icon('edit', $editpath . $row['file_id'], array('title' => t('Edit'))) : l(t('Edit'), $editpath . $row['file_id']));
      $deletelink = ($use_icons ? _filepicker_get_icon('delete', $deletepath . $row['file_id'], array('title' => t('Delete'))) : l(t('Delete'), $deletepath . $row['file_id']));
      $u = user_load(array('uid' => $row['uid']));
      $listlink = l($u->name, $listpath);
      $form['file_name'][$file_id] = array('#value' => $filelink);
      $form['file_title'][$file_id] = array('#value' => check_plain($row['file_title']));
      $form['file_list'][$file_id] = array('#value' => $listlink);
      $form['file_date'][$file_id] = array('#value' => $file_date);
      $form['file_edit'][$file_id] = array('#value' => $editlink);
      $form['file_delete'][$file_id] = array('#value' => $deletelink);
      $cols = 6;
    }
    else {
      if ($public) {
        $editlink = "&nbsp;";
        $deletelink = "&nbsp;";
        if ($src == 'account') {
          $filelink = $file_name;
        }
      }
      else {
        $editlink = ($use_icons ? _filepicker_get_icon('edit', $editpath . $file_id, array('title' => t('Edit'))) : l(t('Edit'), $editpath . $file_id));
        $deletelink = ($use_icons ? _filepicker_get_icon('delete', $deletepath . $file_id, array('title' => t('Delete'))) : l(t('Delete'), $deletepath . $file_id));
      }

      $form['file_name'][$file_id] = array('#value' => $filelink);
      $form['file_title'][$file_id] = array('#value' => check_plain($row['file_title']));
      $form['file_date'][$file_id] = array('#value' => $file_date);
      $form['file_edit'][$file_id] = array('#value' => $editlink);
      $form['file_delete'][$file_id] = array('#value' => $deletelink);
      $cols = 5;
    }
    $files[$file_id] = '';
    $rowct++;
  } // end of while loop

  if ($admin || ! $public) {
    $form['files'] = array(
      '#type' => 'checkboxes',
      '#options' => $files,
    );
  }

  $form['options']['cols'] = array(
    '#type' => 'hidden',
    '#value' => $cols,
  );
  $form['options']['returnpath'] = array(
    '#type' => 'value',
    '#value' => $returnpath,
  );
  $pager = theme('pager', NULL, $max);
  if ($pager) {
    $form['pager'] = array('#value' => $pager);
  }
  $form['#submit'][] = 'filepicker_list_admin_form_submit';
  if ($rowct) {
    return $form;
  }
  return FALSE;
}

/**
 * Submit form
 */
function filepicker_list_admin_form_submit($form, &$form_state) {
  $operation = $form_state['values']['operation'];
  $path = '';
  if (isset($form_state['values']['path'])) {
    $path = $form_state['values']['path'];
  }
  $returnpath = $form_state['values']['returnpath'];
  $files = array_filter($form_state['values']['files']);
  $file_ids = '';
  if ($files) {
    foreach ($files AS $file_id) {
      $file_ids[] = $file_id;
    }
  }
  if (is_array($file_ids)) {
    $sfile_ids = implode('-', $file_ids);
    drupal_goto($path . "/multitask/$operation/$sfile_ids/$returnpath");
  }
  else {
    $rpath = filepicker_multitask_returnpath($returnpath);
    drupal_set_message(t('No files selected'));
    drupal_goto($rpath);
  }
}

/**
 *
 * Menu callback for filepicker multitask.
 * @param $mode
 * @param $sfile_ids
 * @param $returnpath
 */
function filepicker_multitask($mode = '', $sfile_ids = '', $returnpath = '') {

  $cancelpath = filepicker_multitask_returnpath($returnpath);
  $output = '';
  if ($mode && $sfile_ids) {
    switch ($mode) {
      case 'delete':
        // really delete?, auto themed
        $output .= drupal_get_form('filepicker_multitask_delete_form', $sfile_ids, $returnpath);
        $output .= l(t('Cancel'), $cancelpath);
        break;
      case 'groups':
        // select some groups
        $output .= drupal_get_form('filepicker_multitask_groups_form', $sfile_ids, $returnpath);
        $output .= l(t('Cancel'), $cancelpath);
    }
  }
  return $output;
}

function filepicker_multitask_delete_form(&$form_state, $sfile_ids, $returnpath) {

  $form['multitask_delete'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk delete'),
    '#description' => t('Delete all the selected files.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['multitask_delete']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete All'),
  );
  $form['sfile_ids'] = array('#type' => 'value', '#value' => $sfile_ids);
  $form['returnpath'] = array('#type' => 'value', '#value' => $returnpath);
  $file_ids = explode('-', $sfile_ids);
  $form['countnids'] = array('#type' => 'value', '#value' => count($file_ids));
  $form['#submit'][] = 'filepicker_multitask_delete_form_submit';
  return $form;
}

/**
 * Submit form
 */
function filepicker_multitask_delete_form_submit($form, &$form_state) {
  $sfile_ids = $form_state['values']['sfile_ids'];
  $returnpath = $form_state['values']['returnpath'];

  $file_ids = explode('-', $sfile_ids);
  foreach ($file_ids AS $file_id) {
    _filepicker_file_delete($file_id, FALSE, 'admin', TRUE);
  }

  drupal_set_message(t('%c deleted', array('%c' => format_plural( count($file_ids), '1 file', '@count files'))));
  $rpath = filepicker_multitask_returnpath($returnpath);
  drupal_goto($rpath);
}

function filepicker_multitask_groups_form(&$form_state, $sfile_ids, $returnpath) {

  $file_ids = explode('-', $sfile_ids);
  $countnids = count($file_ids);

  $sql = "SELECT uid FROM {filepicker} WHERE file_id = %d";
  $result = db_query($sql, array($file_ids[0]));
  $row = db_fetch_array($result);
  $account = user_load(array('uid' => $row['uid']));
  $grouplist = filepicker_get_groups($account);

  $form['multitask_groups'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk groups management'),
    '#description' => t('Add/Remove all the selected files from groups.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['multitask_groups']['grouplist'] = array(
    '#type' => 'checkboxes',
    '#options' => $grouplist,
    '#title' => t('Your Groups'),
  );
  $form['multitask_groups']['action'] = array(
    '#type' => 'select',
    '#options' => array('add' => t('Add'), 'remove' => t('Remove')),
    '#title' => t('Action'),
    '#description' => t('Add or Remove selected files to one or more selected groups.'),
  );
  $form['multitask_groups']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add/Remove All'),
  );

  $form['sfile_ids'] = array('#type' => 'value', '#value' => $sfile_ids);
  $form['returnpath'] = array('#type' => 'value', '#value' => $returnpath);
  $form['countnids'] = array('#type' => 'value', '#value' => $countnids);
  $form['#submit'][] = 'filepicker_multitask_groups_form_submit';
  return $form;
}

/**
 * Validate form
 */
function filepicker_multitask_groups_form_validate($form, &$form_state) {
  $grouplist = array_filter($form_state['values']['grouplist']);
  if (! count($grouplist)) {
    form_set_error('grouplist', t('You did not select any groups.'));
  }
}

/**
 * Submit form
 */
function filepicker_multitask_groups_form_submit($form, &$form_state) {

  $sfile_ids = $form_state['values']['sfile_ids'];
  $file_ids = explode('-', $sfile_ids);
  $returnpath = $form_state['values']['returnpath'];
  $action = $form_state['values']['action'];
  // list of selected groups
  $grouplist = array_filter($form_state['values']['grouplist']);
  $gids = '';
  foreach ($grouplist AS $gid) {
    $gids[] = $gid;
  }

  if (is_array($gids) && count($file_ids)) {
    foreach ($file_ids AS $file_id) {
      foreach ($gids AS $gid) {
        $sql = "SELECT count(gid) AS ct FROM {filepicker_group_files} WHERE gid = %d AND file_id = %d";
        $result = db_query($sql, array($gid, $file_id));
        $row = db_fetch_array($result);
        $found = FALSE;
        if ($row['ct'] > 0) {
          $found = TRUE;
        }
        if ($action == 'add') {
          if (! $found) {
            // add $file_id to $gid
            $rec['gid'] = $gid;
            $rec['file_id'] = $file_id;
            filepicker_insert_group_file($rec);
          }
        }
        else {
          if ($found) {
            // remove $file_id from $gid
            filepicker_delete_group_file($file_id);
          }
        }
      }
    }
    drupal_set_message(t('%c ', array('%c' => format_plural( count($file_ids), '1 file', '@count files'))) .' '. ($action == 'add' ? t('added') : t('removed')));
  }

  $rpath = filepicker_multitask_returnpath($returnpath);
  drupal_goto($rpath);
}

function filepicker_multitask_returnpath($returnpath) {
  $rpath = '';
  if ($returnpath == 'a') {
    $rpath = FILEPICKER_ADMIN_PATH .'/files/list_all';
  }
  else {
    $a = explode('-', $returnpath);
    if (is_numeric($a[1])) {
      if ($a[0] == 'a') {
        $rpath = FILEPICKER_ADMIN_PATH .'/files/user/'. $a[1] .'/list';
      }
      elseif ($a[0] == 'u') {
        $rpath = 'user/'. $a[1] .'/filepicker/files/list';
      }
    }
  }
  return $rpath;
}


function _filepicker_list_admin($src="iframe", $account=FALSE, $public=FALSE, $range=1, $label='') {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $content = "";
  $forms = array();
  $forms['list_search'] = '';
  $forms['list_groups'] = '';
  $forms['list_public'] = '';
  $forms['list_public_groups'] = '';
  $forms['list_admin'] = '';

  if ( $src == 'admin' && ! $account && variable_get('filepicker_groups_enabled', 1)) {
    $forms['list_public'] = drupal_get_form('filepicker_list_public_form');
  }
  // if there are groups
  if (variable_get('filepicker_groups_enabled', 1)) {
    if ( _filepicker_has_public_groups($user, ($src=='admin' ? TRUE : FALSE)) && $src == 'admin' ) {
      // add groups select here
      $forms['list_public_groups'] = drupal_get_form('filepicker_list_public_groups_form', $user, ($src=='admin' ? TRUE : FALSE));
    }
    if (! $public && _filepicker_has_groups( ($src == 'admin' ? $user : FALSE) ) && filepicker_has_grouplist(($src == 'admin' ? $user : FALSE))) {
      // add groups select here
      $forms['list_groups'] = drupal_get_form('filepicker_list_groups_form', ($src == 'admin' ? $user : FALSE));
    }
  }

  if ($src != 'admin' && isset($user->filepicker_show_list_search_form) && $user->filepicker_show_list_search_form ) {
    $forms['list_search'] = drupal_get_form('filepicker_list_search_form');
  }
  elseif (variable_get('filepicker_show_list_search_form', 1)) {
    $forms['list_search'] = drupal_get_form('filepicker_list_search_form');
  }

  $adminform = drupal_get_form('filepicker_list_admin_form', $src, $account, $public, $range);

  $pref = '<div class="filep_files_list">';
  $suff = '</div>';
  $message = '';
  if ($adminform) {
    if ($public && $src == 'admin') {
      $content .= drupal_get_form('filepicker_list_public_form');
      if ( variable_get('filepicker_groups_enabled', 1) && _filepicker_has_public_groups($user, ($src=='admin' ? TRUE : FALSE))) {
        // add groups select here
        $forms['list_public_groups'] = drupal_get_form('filepicker_list_public_groups_form', $user, TRUE);
      }
    }
    $forms['list_admin'] = $adminform;
  }
  else {
    $ibp = variable_get('filepicker_list_public', 0);
    if ($ibp == 1 || $range == 1) {
      $ibpout = "public";
    }
    elseif ($ibp == 2 || $range == 2) {
      $ibpout = "private";
    }
    else {
      $ibpout = "";
    }
    variable_set('filepicker_list_public', 0);
    if ($searchs) {
      $message = t('Your search for %searchs found nothing', array('%searchs' => $searchs));
      if ($src == 'admin') {
        filepicker_list_search_form_reset_func(TRUE);
      }
      else {
        filepicker_list_search_form_reset_func(FALSE);
      }
    }
    else {
      $message = t('There are no !status files', array('!status' => $ibpout));
    }
  }
  return theme('filepicker_list_admin', $forms, $message, $pref, $suff, $label);
}

function _filepicker_user_has_file($account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $num = 0;
  $result = db_query("SELECT count(file_id) AS ct FROM {filepicker} WHERE uid = '%d'", array($user->uid));
  $row = db_fetch_array($result);
  return $row['ct'];
}

/**
 * groups
 */
function _filepicker_user_has_groups($public = 'all', $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  if ($public == 'yes') {
    $subsql = "AND public = 1";
  }
  elseif ($public == 'no') {
    $subsql = "AND public = 0";
  }
  else {
    $subsql ="";
  }
  $result = db_query("SELECT count(gid) AS ct FROM {filepicker_user_groups}
    WHERE  uid = %d $subsql ", array($user->uid));
  $row = db_fetch_array($result);
  return $row['ct'];

}

/**
 * How many groups a user has with files
 */
function _filepicker_user_has_grouped_file($public = 'all', $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  if ($public == 'yes') {
    $subsql = "AND public = 1";
  }
  elseif ($public == 'no') {
    $subsql = "AND public = 0";
  }
  else {
    $subsql ="";
  }

  $result = db_query("SELECT count(DISTINCT i.file_id) AS ct FROM {filepicker_group_files} i, {filepicker_user_groups} g
    WHERE g.uid = %d AND g.gid = i.gid $subsql ", array($user->uid));
  $row = db_fetch_array($result);
  return $row['ct'];
}

/**
 * count of groups per user
 */
function filepicker_has_groups($account=FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $result = db_query("SELECT count(gid) as gidct FROM {filepicker_user_groups} WHERE uid = %d", array($user->uid));
  $row = db_fetch_array($result);
  return $row['gidct'];
}

/**
 * get all the groups for the current user
 */
function filepicker_get_groups($account=FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $result = db_query("SELECT * FROM {filepicker_user_groups} WHERE uid = %d", array($user->uid));
  $count = 0;
  while ($row = db_fetch_array($result)) {
    $data[$row['gid']] = $row['group_name'] . ($row['public'] ? ' - '. t('Public') : ' - '. t('Private'));
    $count++;
  }
  if ($count) {
    return $data;
  }
  return FALSE;
}

/**
 * get all for a group
 */
function filepicker_get_user_group($gid, $obj=TRUE) {
  $result = db_query("SELECT * FROM {filepicker_user_groups} WHERE gid = %d", array($gid));
  if ($obj) {
    return db_fetch_object($result);
  }
  return db_fetch_array($result);
}

/**
 * get the gid of the selected group
 */
function filepicker_get_user_group_state($state=1, $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $result = db_query("SELECT gid FROM {filepicker_user_groups} WHERE state=%d AND uid=%d", array($state, $user->uid));
  $ct = 0;
  while ($row = db_fetch_array($result)) {
    $data[] = $row['gid'];
    $ct++;
  }
  if ($ct) {
    return $data;
  }
  return FALSE;
}

/**
 * set group state
 */
function filepicker_set_user_group_state($state, $gid, $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  db_query("UPDATE {filepicker_user_groups} SET state=0 WHERE uid=%d AND state=1", array($user->uid));
  db_query("UPDATE {filepicker_user_groups} SET state=%d WHERE gid=%d", array($state, $gid));
}

/**
 * build groups select
 */
function filepicker_get_grouplist($account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $grouplist = array('0' => 'All');
  $result = db_query("
  SELECT DISTINCT g.gid, g.group_name, g.public
  FROM {filepicker_user_groups} g, {filepicker_group_files} i
  WHERE g.uid=%d AND g.gid = i.gid", array($user->uid));
  while ($row = db_fetch_array($result)) {
    $grouplist[$row['gid']] = $row['group_name'] . (user_access('use public filepicker') && variable_get('filepicker_public_enabled', 1) ? ($row['public'] ? ' - '. t('Public') : ' - '. t('Private')) : '');
  }
  return $grouplist;
}

/**
 * get how many groups
 */
function filepicker_has_grouplist($account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $ct = 0;
  $result = db_query("
  SELECT DISTINCT g.gid
  FROM {filepicker_user_groups} g, {filepicker_group_files} i
  WHERE g.uid=%d AND g.gid = i.gid", array($user->uid));
  while ($row = db_fetch_array($result)) {
    $ct++;
  }
  return $ct;
}

/**
 * for public dropdown
 */
function filepicker_get_public_grouplist($account = FALSE, $admin = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $grouplist = array('0' => 'All');
  $tmp = '';
  $result = db_query("
    SELECT g.gid, g.group_name, g.avail_roles
    FROM {filepicker_user_groups} AS g
    WHERE g.public = 1");
  $rowct = 0;
  while ($row = db_fetch_array($result)) {
    $tmp[$rowct]['gid'] = $row['gid'];
    $tmp[$rowct]['group_name'] = $row['group_name'];
    $tmp[$rowct]['avail_roles'] = $row['avail_roles'];
    $rowct++;
  }
  // filter for role
  if (is_array($tmp)) {
    for ($ct = 0; $ct < $rowct; $ct++) {
      if (! $admin) {
        if ($tmp[$ct]['avail_roles'] != 'all') {
          $role = $tmp[$ct]['avail_roles'];
          if (filepicker_user_has_role($role, $user)) {
            $grouplist[$tmp[$ct]['gid']] = $tmp[$ct]['group_name'];
          }
        }
        else {
          $grouplist[$tmp[$ct]['gid']] = $tmp[$ct]['group_name'];
        }
      }
      else {
        $grouplist[$tmp[$ct]['gid']] = $tmp[$ct]['group_name'];
      }
    }
    return $grouplist;
  }
  return FALSE;
}

/**
 * how many public groups
 */
function _filepicker_has_public_groups($account=FALSE, $admin = FALSE) {
  if (! variable_get('filepicker_groups_enabled', 0)) {
    return 0;
  }
  if ($admin && variable_get('filepicker_list_public', 0) != 1) {
    return 0;
  }
  $list = filepicker_get_public_grouplist($account, $admin);
  if (is_array($list)) {
    return count($list);
  }
  return 0;
}

/**
 * how many groups
 */
function _filepicker_has_groups($account=FALSE) {
  if (! variable_get('filepicker_groups_enabled', 0)) {
    return 0;
  }
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $result = db_query("SELECT COUNT(gid) AS ct FROM {filepicker_user_groups} WHERE uid = %d", array($user->uid));
  $row = db_fetch_array($result);
  return $row['ct'];
}

/**
 * get enabled groups that have files. usually just one
 */
function filepicker_get_enabled_group($account = FALSE) {
  if (! variable_get('filepicker_groups_enabled', 0)) {
    return FALSE;
  }
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $result = db_query("
  SELECT DISTINCT g.gid, g.group_name
  FROM {filepicker_user_groups} g, {filepicker_group_files} i
  WHERE g.uid=%d AND g.gid = i.gid AND g.state=1", array($user->uid));
  $ct = 0;
  while ($row = db_fetch_array($result)) {
    $data[] = $row['gid'];
    $ct++;
  }
  if ($ct) {
    return $data;
  }
  return FALSE;
}

/**
 * all the groups for the current user which have files attached
 */
function filepicker_list_groups_form(&$form_state, $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $grouplist = filepicker_get_grouplist($user);
  if ($account) {
    $enabledlist = variable_get('filepicker_currentgroup', 0);
  }
  else {
    $enabledlist = filepicker_get_enabled_group($user);
  }

  $form['gid'] = array(
    '#type' => 'select',
    '#default_value' => $enabledlist,
    '#options' => $grouplist,
    '#title' => t('Group'),
  );
  if ($account) {
    $form['uid'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );

  return $form;
}

/**
 * Submit list groups form
 */
function filepicker_list_groups_form_submit($form, &$form_state) {
  // need to get the users gids
  $account = FALSE;
  if ( isset($form_state['values']['uid'])) {
    $account = user_load(array('uid' => $form_state['values']['uid']));
    if ($form_state['values']['gid']) {
    variable_set('filepicker_currentgroup', $form_state['values']['gid']);
    }
    else {
    variable_set('filepicker_currentgroup', 0);
    }
  }
  else {
    $gids = filepicker_get_groups($account);
    $gids = array_keys($gids);
    foreach ($gids AS $gid) {
      $state = 0;
      if ( $gid == $form_state['values']['gid'] ) {
        $state = 1;
      }
      db_query("UPDATE {filepicker_user_groups} SET state=%d WHERE gid=%d", array($state, $gid));
    }
  }
}

/**
 * Submit public list groups form
 *
 * @param $account
 *   Optional,
 * @param $admin
 *   Optional, sets where the form is coming from
 * @return
 *   Returns the form.
 */
function filepicker_list_public_groups_form(&$form_state, $account = FALSE, $admin = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  // all the groups for the current user which have files attached
  $grouplist = filepicker_get_public_grouplist($user, $admin);
  if ($admin) {
    $enabledlist = variable_get('filepicker_public_currentgroup', 0);
  }
  else {
    $enabledlist = (isset($user->filepicker_public_currentgroup) ? $user->filepicker_public_currentgroup : 0);
  }

  $form['gid'] = array(
    '#type' => 'select',
    '#default_value' => $enabledlist,
    '#options' => $grouplist,
    '#title' => t('Public Group'),
  );
  if ($admin) {
    $form['admin'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );

  return $form;
}

/**
 * Submit public list groups form
 */
function filepicker_list_public_groups_form_submit($form, &$form_state) {

  if ( isset($form_state['values']['admin'])) {
    if ($form_state['values']['gid'] > 0) {
    variable_set('filepicker_public_currentgroup', $form_state['values']['gid']);
    }
    else {
    variable_del('filepicker_public_currentgroup');
    }
  }
  else {
    global $user;
    if ($form_state['values']['gid'] > 0) {
      user_save($user, array('filepicker_public_currentgroup' => $form_state['values']['gid']));
    }
    else {
      user_save($user, array('filepicker_public_currentgroup' => NULL));
    }
  }
}

/**
 * Insert a form into the edit file page to allow the file to be associated with a group.
 *
 * @param $file_id
 *   The id of the file to be inserted.
 * @param $account
 *   Optional, allows the administrator to edit user settings.
 * @return
 *   Returns the group file form.
 */
function filepicker_group_files_form(&$form_state, $file_id, $account = FALSE) {

  $grouplist = filepicker_get_groups($account);
  $enabledlist = filepicker_get_file_groups($file_id);

  $form['group_files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Groups'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['group_files']['grouplist'] = array(
    '#type' => 'checkboxes',
    '#default_value' => $enabledlist,
    '#options' => $grouplist,
    '#title' => t('Your Groups'),
  );
  $form['group_files']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save group settings'),
    );
  $form['file_id'] = array(
    '#type' => 'value',
    '#value' => $file_id,
  );
  return $form;
}

/**
 * Submit group files form
 */
function filepicker_group_files_form_submit($form, &$form_state) {
  // delete all the entries for this file and rebuild with the new ones;
  $file_id = $form_state['values']['file_id'];
  filepicker_delete_group_file($file_id);
  $grouplist = $form_state['values']['grouplist'];
  $inserted = FALSE;
  foreach ($grouplist AS $gid) {
    if ($gid > 0) {
      $record = array('gid' => $gid, 'file_id' => $file_id);
      filepicker_insert_group_file($record);
      $inserted = TRUE;
    }
  }
  if (! $inserted) {
    $gid = filepicker_get_user_group_state();
    if ($gid) {
      $ids = filepicker_get_files_by_group($gid);
      if (! $ids) {
        global $user;
        db_query("UPDATE {filepicker_user_groups} SET state=0 WHERE uid=%d AND state=1", array($user->uid));
      }
    }
  }
}

function filepicker_get_file_groups($file_id) {
  $data = array();
  $result = db_query("SELECT gid FROM {filepicker_group_files} WHERE file_id = %d", array($file_id));
  while ($row = db_fetch_array($result)) {
    $data[] = $row['gid'];
  }
  return $data;
}

function filepicker_get_files_by_group($gid) {
  $result = db_query("SELECT file_id FROM {filepicker_group_files} WHERE gid = %d", array($gid));
  $ct = 0;
  while ($row = db_fetch_array($result)) {
    $data[] = $row['file_id'];
    $ct++;
  }
  if ($ct) {
    return $data;
  }
  return FALSE;
}

function filepicker_delete_group_file($file_id) {
  if (! db_query("DELETE FROM {filepicker_group_files} WHERE file_id=%d", array($file_id))) {
    drupal_set_message(t('Error while trying to delete your group.'), 'error');
  }
}

function filepicker_insert_group_file($record) {
  if ($record['gid'] && $record['file_id']) {
    if (! db_query(
      "INSERT INTO {filepicker_group_files} (gid, file_id) VALUES (%d, %d)",
      array($record['gid'], $record['file_id']))) {
      drupal_set_message(t('Error while trying to insert your group.'), 'error');
    }
  }
}

function filepicker_get_files_directory() {
  $drupaldir = str_replace('/', DIRECTORY_SEPARATOR, getcwd()) . DIRECTORY_SEPARATOR;
  $dir = $drupaldir . file_directory_path() . DIRECTORY_SEPARATOR . FILEPICKER_FILES_DIR;
  return $dir;
}

function _filepicker_get_file($file_id, $checkuser=TRUE, $account = FALSE) {
  if (is_object($account)) {
    $user = $account;
  }
  else {
    global $user;
  }

  $result = db_query_range("SELECT * FROM {filepicker} WHERE file_id = '%d'", $file_id, 0, 1);
    $file = db_fetch_array($result);
    if ( count($file) ) {
      if (($file['uid'] != $user->uid) && $checkuser) {
        drupal_set_message(t('This file does not belong to you.'), 'error');
        watchdog('filepicker', 'User uid %d attempted to edit file belonging to user uid %d', array($user->uid, $file['uid']), WATCHDOG_WARNING);
        return FALSE;
      }
      return $file;
    }
  return FALSE;
}

/**
 * statistics
 */
function filepicker_group_stats($account = FALSE, $label = '') {
  // stats
  $usercount = FALSE;
  $bytecount = 0;
  if ($account) {
    if (is_numeric($account) && $account == -1) {
      $allcount = _filepicker_user_has_file();
      $totcount = _filepicker_user_has_grouped_file('all');
      $publiccount = _filepicker_user_has_grouped_file('yes');
      $nopubliccount = _filepicker_user_has_grouped_file('no');
      $groupcount = _filepicker_user_has_groups('all');
      $publicgroupcount = _filepicker_user_has_groups('yes');
      $nopublicgroupcount = _filepicker_user_has_groups('no');
      $bytecount = filepicker_get_all_bytes(-1);
    }
    else {
      $allcount = _filepicker_user_has_file($account);
      $totcount = _filepicker_user_has_grouped_file('all', $account);
      $publiccount = _filepicker_user_has_grouped_file('yes', $account);
      $nopubliccount = _filepicker_user_has_grouped_file('no', $account);
      $groupcount = _filepicker_user_has_groups('all', $account);
      $publicgroupcount = _filepicker_user_has_groups('yes', $account);
      $nopublicgroupcount = _filepicker_user_has_groups('no', $account);
      $bytecount = filepicker_get_all_bytes($account);
    }
  }
  else {
    // filepicker users
    $result = db_query("SELECT count(DISTINCT uid) AS ct FROM {filepicker_user_groups}");
    $row = db_fetch_array($result);
    $usercount = $row['ct'];
    // all groups
    $result = db_query("SELECT count(gid) AS ct FROM {filepicker_user_groups}");
    $row = db_fetch_array($result);
    $groupcount = $row['ct'];
    // public groups
    $result = db_query("SELECT count(gid) AS ct FROM {filepicker_user_groups} WHERE public = 1");
    $row = db_fetch_array($result);
    $publicgroupcount = $row['ct'];
    // private groups
    $result = db_query("SELECT count(gid) AS ct FROM {filepicker_user_groups} WHERE public = 0");
    $row = db_fetch_array($result);
    $nopublicgroupcount = $row['ct'];
    // all files
    $result = db_query("SELECT count(file_id) AS ct FROM {filepicker}");
    $row = db_fetch_array($result);
    $allcount = $row['ct'];
    // grouped files
    $result = db_query("SELECT count(DISTINCT gi.file_id) AS ct FROM {filepicker_group_files} gi, {filepicker_user_groups} g WHERE g.gid = gi.gid ");
    $row = db_fetch_array($result);
    $totcount = $row['ct'];
    // public files
    $result = db_query("SELECT COUNT(i.file_id) AS ct FROM {filepicker} i, {filepicker_user_groups} g, {filepicker_group_files} gi WHERE i.file_id = gi.file_id AND g.gid = gi.gid AND g.public = 1");
    $row = db_fetch_array($result);
    $publiccount = $row['ct'];
    // private files
    $result = db_query("SELECT COUNT(i.file_id) AS ct FROM {filepicker} i, {filepicker_user_groups} g, {filepicker_group_files} gi WHERE i.file_id = gi.file_id AND g.gid = gi.gid AND g.public = 0");
    $row = db_fetch_array($result);
    $nopubliccount = $row['ct'];

    $bytecount = filepicker_get_all_bytes();
  }
  $bytecount = _filepicker_bkmg($bytecount);

  $header = array(
    array('data' =>  t('Group statistics'), 'colspan' => 2),
    array('data' =>  t('File statistics'), 'colspan' => 2),
  );

  if ( user_access('use public filepicker') && variable_get('filepicker_public_enabled', 1) ) {
    $rows = array(
      array(t('Groups') .": ", $groupcount,                 t('Files') .": ", $allcount),
      array(t('Public groups') .": ", $publicgroupcount,    t('Public files') .": ", $publiccount),
      array(t('Private groups') .": ", $nopublicgroupcount, t('Private files') .": ", $nopubliccount),
      array( '', '',                                        t('Grouped files') .": ", $totcount),
      array( '', '',                                        t('Ungrouped files') .": ", $allcount-$totcount),
      array(($usercount ? t('Users') .": " : ''), ($usercount ? $usercount : ''), t('Space used')  .": ", $bytecount),
    );

  }
  else {
    $rows = array(
      array(t('Groups') .": ", $groupcount, t('Files') .": ", $allcount),
      array( '', '',                        t('Grouped files') .": ", $totcount),
      array( '', '',                        t('Ungrouped files') .": ", $allcount-$totcount),
      array(($usercount ? t('Users') .": " : ''), ($usercount ? $usercount : ''), t('Space used')  .": ", $bytecount),
    );
  }
  return theme('filepicker_stats', $header, $rows, '<div class="filep_groups_info">', '</div>', $label);
}

/**
 * Function to display the public status selection form
 *
 * @return
 *   Returns the form.
 */
function filepicker_list_public_form(&$form_state) {
  $list = array(
    0 => t('All'),
    1 => t('Public'),
    2 => t('Private'),
  );
  $form['filepicker_list_public'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('filepicker_list_public', 0),
    '#options' => $list,
    '#title' => t('Show'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );
  return $form;
}

/**
 * Submit form
 */
function filepicker_list_public_form_submit($form, &$form_state) {
  variable_set('filepicker_list_public', $form_state['values']['filepicker_list_public']);
}

function _filepicker_get_bytes($file_id, $account = FALSE) {
  if ($account) {
    $user = $account;
    $userdir = array('name' => $user->name , 'uid' => $user->uid);
  }
  else {
    global $user;
    $userdir = FALSE;
  }

  $tot = 0;
  $file = _filepicker_get_file($file_id, FALSE, $user);
  if ($file) {
    $path = filepicker_get_path(FALSE, $userdir);
    if (file_exists($path . '/'. $file['file_name'])) {
      $tot = filesize($path . '/'. $file['file_name'] );
    }
  }
  else {
    drupal_set_message(t('File not found.'), 'error');
  }
  return $tot;
}

function filepicker_get_all_bytes($account = FALSE) {
  $tot = 0;
  $olduid = 0;
  $sql = 'SELECT file_id, uid FROM {filepicker} ';
  if (is_object($account) ) {
    $sql .= 'WHERE uid = '. $account->uid;
    $user = $account;
  }
  elseif ($account == -1) {
    global $user;
    $sql .= 'WHERE uid = '. $user->uid;
  }
  $result = db_query($sql);
  while ( $row = db_fetch_array($result) ) {
    if (! $account && $olduid <> $row['uid'] ) {
      $user = user_load(array('uid' => $row['uid']));
    }
    $tot += _filepicker_get_bytes($row['file_id'], $user);
    $olduid = $row['uid'];
  }
  return $tot;
}

function _filepicker_bkmg($number) {
  $inc = 1000;
  $count = 1000;
  $symarr = array('K', 'M', 'G', 'T');
  $sym = 'B';
  while ($number > $count) {
    $count = $count * $inc;
    $sym = array_shift($symarr);

  }
  if ($number < $inc ) {
    if ($number > 0) {
      return ($number-1 .' '. $sym);
    }
    return ("0 $sym");
  }
  return (round(($number/$count)*$inc, 2) .' '. $sym);
}

function filepicker_get_quota_list($key = 'x') {
  $list = array(
    0 => t('Unlimited'),
    1 => t('1 Meg'),
    5 => t('5 Meg'),
    10 => t('10 Meg'),
    25 => t('25 Meg'),
    50 => t('50 Meg'),
    100 => t('100 Meg'),
    250 => t('250 Meg'),
    500 => t('500 Meg'),
    750 => t('750 Meg'),
    1000 => t('1 Gig'),
    2000 => t('2 Gig'),
    5000 => t('5 Gig'),
  );

  if ($key == 'x') {
    return $list;
  }

  $value = $list[$key-1];
  return $value;
}

/**
 * Checks quotas
 *
 * @param $src
 *   Tells the function where the request is coming from
 * @param $account
 *   Optional user account object.
 * @param $label
 *   Optional label to pass through to the theme
 * @param $help
 *   Optional help to pass through to the theme
 * @return
 *   Returns the quota message along with the upload form, all themed
 */
function filepicker_quota_ok($src, $account = FALSE, $label="", $help="") {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }

  $ret = _filepicker_quota_check($src, $account);
  $quota_ok = $ret[0];
  $message1 = $ret[1];
  $message2 = $ret[2];
  $form = '';

  if ($quota_ok) {
    if ($account) {
      if ($src == 'admin') {
        $form = drupal_get_form('filepicker_upload_form', $user, TRUE);
      }
      elseif ($src == 'user') {
        $form = drupal_get_form('filepicker_upload_form', $user);
      }
    }
    else {
      $form = drupal_get_form('filepicker_upload_form');
    }
  }
  return theme('filepicker_quota_message', $message1, $message2, $form, $label, $help);
}

function _filepicker_quota_check($src, $account = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $usedbytes = filepicker_get_all_bytes($user)+1;
  $usedbytesprint = _filepicker_bkmg($usedbytes);
  $quota = 0;
  $quota_enabled = variable_get('filepicker_quota_enable', 1);
  if ($quota_enabled) {
    if (variable_get('filepicker_quota_byrole', 0)) {
      $roleid = variable_get('filepicker_quota_role', 2);
      if (filepicker_user_has_role($roleid, $user) && $user->uid > 1) {
        $quota = variable_get('filepicker_quota_default', 0);
      }
    }
    else {
      $quota = (isset($user->filepicker_quota) ? $user->filepicker_quota : variable_get('filepicker_quota_default', 0));
    }
    if ($quota > 0) {
      $quota_ok = (( ($quota*1000000) >  $usedbytes) ? TRUE : FALSE );
    }
    else {
      $quota_ok = TRUE;
    }
  }
  else {
    $quota_ok = TRUE;
  }
  $filetot = _filepicker_user_has_file($user);
  $pl = format_plural($filetot, '1 file', '@count files');
  $message1 = '';
  $message2 = '';
  if ($quota_enabled) {
    if ($quota > 0) {
      $pused = round($usedbytes / ($quota*1000000) * 100, 2);
      $quotaprint = filepicker_get_quota_list($quota+1);
      if ($src == 'admin') {
        $message1 = t('The quota for %name is %quotaprint and has used %pused percent, or %usedbytesprint in %pl', array('%name' => $user->name, '%quotaprint' => $quotaprint, '%pused' => $pused, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
      }
      else {
        $message1 = t('Your quota is %quotaprint and you have used %pused percent, or %usedbytesprint in %pl', array('%quotaprint' => $quotaprint, '%pused' => $pused, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
      }
    }
    else {
      $quotaprint = filepicker_get_quota_list($quota+1);
      if ($src == 'admin') {
        $message1 = t('The quota for %name is %quotaprint and has used %usedbytesprint in %pl', array('%name' => $user->name, '%quotaprint' => $quotaprint, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
      }
      else {
        $message1 = t('Your quota is %quotaprint and you have used %usedbytesprint in %pl', array('%quotaprint' => $quotaprint, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
      }
    }
  }
  else {
    if ($src == 'admin') {
      $message1 = t('%name has used %usedbytesprint in %pl', array('%name' => $user->name, '%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
    }
    else {
      $message1 = t('You have used %usedbytesprint in %pl', array('%usedbytesprint' => $usedbytesprint, '%pl' => $pl));
    }
  }
  if (! $quota_ok ) {
    if ($src == 'admin') {
      $message2 = t('%name has used all of quota, please delete some files to make some room.', array('%name' => $user->name));
    }
    else {
      $message2 = t('You have used all of your quota, please delete some files to make some room.');
    }
  }
  return array($quota_ok, $message1, $message2);
}

/**
 * Function to display the file search form
 *
 * @param $account
 *   Optional user account object.
 * @param $admin
 *   Optional admin flag.
 * @return
 *   Returns the search form.
 */
function filepicker_list_search_form(&$form_state, $account = FALSE, $admin = FALSE) {
  if ($account) {
    $user = $account;
  }
  else {
    global $user;
  }
  $sarr = '';
  if ($admin) {
    $search = variable_get('filepicker_list_search', '');
    $sarr = variable_get('filepicker_list_search_opts', '');
    $form['admin'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
  else {
    $search = (isset($user->filepicker_list_search) ? $user->filepicker_list_search : '');
    $sarr = (isset($user->filepicker_list_search_opts) ? $user->filepicker_list_search_opts : '');
  }

  $form['filepicker_list_search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
    '#size' => 10,
    '#default_value' => $search,
  );
  $form['filepicker_list_search_by_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('By Name'),
    '#default_value' => ( is_array($sarr) ? $sarr['name'] : 0),
  );
  $form['filepicker_list_search_by_desc'] = array(
    '#type' => 'checkbox',
    '#title' => t('By Description'),
    '#default_value' => ( is_array($sarr) ? $sarr['desc'] : 0),
  );
  $form['filepicker_list_search_by_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('By Title'),
    '#default_value' => ( is_array($sarr) ? $sarr['title'] : 0),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
  );
    $form['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
      '#submit' => array('filepicker_list_search_form_reset'),
    );

  return $form;
}

/**
 * Submit form
 */
function filepicker_list_search_form_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['filepicker_list_search'] != '') {
    $arr = array(
        'name' => $form_state['values']['filepicker_list_search_by_name'],
        'desc' => $form_state['values']['filepicker_list_search_by_desc'],
        'title' => $form_state['values']['filepicker_list_search_by_title']);
    $search = $form_state['values']['filepicker_list_search'];
    if (isset($form_state['values']['admin'])) {
      variable_set('filepicker_list_search', $search);
      variable_set('filepicker_list_search_opts', $arr);
    }
    else {
      user_save($user, array('filepicker_list_search' => $search));
      user_save($user, array('filepicker_list_search_opts' => $arr));
    }
  }
  else {
    if (isset($form_state['values']['admin'])) {
      variable_del('filepicker_list_search');
      variable_del('filepicker_list_search_opts');
    }
    else {
      user_save($user, array('filepicker_list_search' => NULL));
      user_save($user, array('filepicker_list_search_opts' => NULL));
    }
  }
}

/**
 * Submit Reset button.
 */
function filepicker_list_search_form_reset($form, &$form_state) {
  filepicker_list_search_form_reset_func( (isset($form_state['values']['admin']) ? TRUE : FALSE));
}

function filepicker_list_search_form_reset_func($admin = FALSE) {
  global $user;
    if ($admin) {
      variable_del('filepicker_list_search');
      variable_del('filepicker_list_search_opts');
    }
    else {
      user_save($user, array('filepicker_list_search' => NULL));
      user_save($user, array('filepicker_list_search_opts' => NULL));
    }
}

function _filepicker_search_opts($searchs) {
  $search_opts = variable_get('filepicker_list_search_opts', array());
  if (! isset($search_opts['name'])) {
    $search_opts['name'] = FALSE;
  }
  if (! isset($search_opts['desc'])) {
    $search_opts['desc'] = FALSE;
  }
  if (! isset($search_opts['title'])) {
    $search_opts['title'] = FALSE;
  }

  if (   $search_opts['name']
    && ! $search_opts['desc']
    && ! $search_opts['title']) {
    $s = " AND i.file_name LIKE '%%%s%%' ";
    $sarr = array($searchs);
  }
  elseif ( $search_opts['name']
    &&     $search_opts['desc']
    &&   ! $search_opts['title']) {
    $s = " AND (i.file_name LIKE '%%%s%%' OR i.file_description LIKE '%%%s%%') ";
    $sarr = array($searchs, $searchs);
  }
  elseif ( $search_opts['name']
    &&   ! $search_opts['desc']
    &&     $search_opts['title']) {
    $s = " AND (i.file_name LIKE '%%%s%%' OR i.file_title LIKE '%%%s%%') ";
    $sarr = array($searchs, $searchs);
  }
  elseif (! $search_opts['name']
    &&      $search_opts['desc']
    &&      $search_opts['title']) {
    $s = " AND (i.file_description LIKE '%%%s%%' OR i.file_title LIKE '%%%s%%') ";
    $sarr = array($searchs, $searchs);
  }
  elseif (! $search_opts['name']
    &&    ! $search_opts['desc']
    &&      $search_opts['title']) {
    $s = " AND i.file_title LIKE '%%%s%%' ";
    $sarr = array($searchs);
  }
  elseif (! $search_opts['name']
    &&      $search_opts['desc']
    &&    ! $search_opts['title']) {
    $s = " AND i.file_description LIKE '%%%s%%' ";
    $sarr = array($searchs);
  }
  else {
    $s = " AND (i.file_name LIKE '%%%s%%' OR i.file_description LIKE '%%%s%%' OR i.file_title LIKE '%%%s%%') ";
    $sarr = array($searchs, $searchs, $searchs);
  }
  return (array(0 => $s, 1 => $sarr));
}


/**
 * Function to insert the file data into db
 *
 * @param $uid
 *   Required user id
 * @param $file_name
 *   Required file name
 * @param $file_title
 *   Optional file title
 * @return
 *   Returns the current file id
 */
function filepicker_insert_file($uid, $file_name, $file_title="") {

  if (! $uid || ! $file_name) {
    return FALSE;
  }
  $date = time();
  $result = db_query("INSERT INTO {filepicker} (uid, file_name, file_title, file_date)
  VALUES ('%d', '%s', '%s', '%s')", array($uid, $file_name, $file_title, $date));
  if ($result) {
    $nextfileid = db_last_insert_id("filepicker", 'file_id');
    return $nextfileid;
  }
  return FALSE;
}

/**
 * Helper function to check if a user has a specific role
 */
function filepicker_user_has_role($role, $user=NULL) {
  if ($user == NULL) {
    global $user;
  }
  // first check if $role is numeric or string
  if (is_numeric($role) ) {
    if (is_array($user->roles) && in_array($role, array_keys($user->roles))) {
      return TRUE;
    }
  }
  else {
    if (is_array($user->roles) && in_array($role, array_values($user->roles))) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Function to get an icon
 * Derived from invoice module
 *
 * @param $name
 *   Name of icon without extension.
 * @param $url
 *   URL to link the icon to.
 * @param $attributes
 *   Any optional HTML attributes.
 * @param $extension
 *   The file extension.
 * @return
 *   The icon string.
 */
function _filepicker_get_icon($name, $url = NULL, $attributes = array(), $extension = 'png') {
  if (empty($attributes['alt'])) {
    $attributes['alt'] = $attributes['title'];
  }

  $file_addition = '';
  foreach ($attributes as $key => $value) {
    $file_addition .= ' '. $key .'="'. $value .'"';
  }

  $icon = '<img src="'. base_path() . drupal_get_path('module', 'filepicker') .'/images/'. $name .'.'. $extension .'"'. $file_addition .' />';
  if (!empty($url)) {
    $icon = l($icon, $url, array('html' => TRUE));
  }
  return $icon;
}

function filepicker_group_files_count($gid) {
  $sql = "SELECT COUNT(file_id) AS ct FROM {filepicker_group_files} WHERE gid = %d";
  $result = db_query($sql, array($gid));
  $row = db_fetch_array($result);
  return $row['ct'];
}

function filepicker_get_info($file) {

  $filepath = filepicker_get_path(FALSE, array('uid' => $file['uid']));
  $info['file_size'] = filesize($filepath . $file['file_name']);
  return $info;
}

function filepicker_validate_is_file($filename) {
  if (variable_get('filepicker_upload_mimetypes', 0)) {
    $mimetype = file_get_mimetype($filename);
    if ($mimetype == 'application/octet-stream') {
      return '';
    }
  }
  if (preg_match('!.*\.(.*)$!i', $filename, $matches)) {
    if ($matches[1]) {
      $filext = drupal_strtolower($matches[1]);
      // TODO add a restricted list here
      $extensions = explode(' ', variable_get('filepicker_upload_extensions', 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp'));
      if (in_array($filext, $extensions)) {
        return $matches[1];
      }
    }
  }
  return '';
}

/**
 * all iframe links pass through here
 */
function filepicker_box() {
  $a1 = FALSE;
  $a2 = 0;

  if (arg(1)) {
    $a1 = arg(1);
  }
  if (arg(2) && is_numeric(arg(2))) {
    $a2 = arg(2);
  }

  if ($a1 == 'list') {
    $content = filepicker_list($a2);
  }
  elseif ($a1 == 'list_public') {
    $content = filepicker_list_public($a2);
  }
  elseif ($a1 == 'groups') {
    $content = filepicker_groups();
  }
  elseif ($a1 == 'edit') {
    $content = filepicker_file_edit($a2);
  }
  else {
    module_load_include('inc', 'filepicker', 'filepicker.upload');
    $content = filepicker_upload();
  }

  drupal_add_css(FILEPICKER_PATH .'/filepicker.css');

  $output = theme('filepicker', $content);
  print $output;
  exit;

}

/**
 * callback for uploadprogress information function.
 */
function filepicker_uploadprogress_callback($progress_key='') {

  if (! $progress_key) {
    $progress_key = $_GET['key'];
  }

  if (variable_get('filepicker_uploadprogress_server', '') && function_exists('uploadprogress_get_info') && $progress_key) {
    $status = uploadprogress_get_info($progress_key);
    if ($status['bytes_total']) {
      $status['status'] = 1;
      $status['percentage'] = round($status['bytes_uploaded']/$status['bytes_total'] * 100, 0);
      $eta = sprintf("%02d:%02d", $status['est_sec'] / 60, $status['est_sec'] % 60 );
      $speed = _filepicker_bkmg($status['speed_average']);
      $bytes_total = _filepicker_bkmg($status['bytes_total']);
      $status['message'] = t('Filesize: !bytes_total. !eta left at !speed/sec.', array('!eta' => $eta, '!speed' => $speed, '!bytes_total' => $bytes_total));
    }
    else {
      $status['status'] = 1;
      $status['percentage'] = -1;
      $status['message'] = variable_get('filepicker_upload_progress_message', t('Processing form... please wait.'));
    }
    echo json_encode($status);
  }

  exit;
}

