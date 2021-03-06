<?php

/*
 +-----------------------------------------------------------------------+
 | program/steps/mail/pagenav.inc                                        |
 |                                                                       |
 | This file is part of the Roundcube Webmail client                     |
 | Copyright (C) 2005-2009, The Roundcube Dev Team                       |
 |                                                                       |
 | Licensed under the GNU General Public License version 3 or            |
 | any later version with exceptions for skins & plugins.                |
 | See the README file for a full license statement.                     |
 |                                                                       |
 | PURPOSE:                                                              |
 |   Updates message page navigation controls                            |
 |                                                                       |
 +-----------------------------------------------------------------------+
 | Author: Aleksander Machniak <alec@alec.pl>                            |
 +-----------------------------------------------------------------------+

 $Id: show.inc 4176 2010-11-04 09:59:55Z alec $

*/

$uid   = get_input_value('_uid', RCUBE_INPUT_GET);
$index = $RCMAIL->storage->index(null, $_SESSION['sort_col'], $_SESSION['sort_order']);
$cnt   = $index->count_messages();

if ($cnt && ($pos = $index->exists($uid, true)) !== false) {
    $prev  = $pos ? $index->get_element($pos-1) : 0;
    $first = $pos ? $index->get_element('FIRST') : 0;
    $next  = $pos < $cnt-1 ? $index->get_element($pos+1) : 0;
    $last  = $pos < $cnt-1 ? $index->get_element('LAST') : 0;
}

// Set UIDs and activate navigation buttons
if ($prev) {
    $OUTPUT->set_env('prev_uid', $prev);
    $OUTPUT->command('enable_command', 'previousmessage', 'firstmessage', true);
}
if ($next) {
    $OUTPUT->set_env('next_uid', $next);
    $OUTPUT->command('enable_command', 'nextmessage', 'lastmessage', true);
}
if ($first)
    $OUTPUT->set_env('first_uid', $first);
if ($last)
    $OUTPUT->set_env('last_uid', $last);

// Don't need a real messages count value
$OUTPUT->set_env('messagecount', 1);

// Set rowcount text
$OUTPUT->command('set_rowcount', rcube_label(array(
    'name' => 'messagenrof',
    'vars' => array('nr'  => $pos+1, 'count' => $cnt)
)));

$OUTPUT->send();

