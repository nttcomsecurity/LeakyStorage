<?php
if (isset($_GET['filename']) and isset($_GET['content'])) {
        $myfile = fopen('uploads/' . $_GET['filename'] .'-' .  date('Y-m-d-H-i-s'), 'a+');
        fputs($myfile, $_GET['content']);
        fclose($myfile);
}
?>
