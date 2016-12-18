<?php
if (isset($_GET['filename']) and isset($_GET['content'])) {
        $myfile = fopen('uploads/' . $_GET['filename'] .'-' .  date('Y-m-d-H-i-s'), 'a+');
        for ($i = 0; $i < strlen($_GET['content']); $i += 2)
        {
                fputs($myfile, chr(hexdec($_GET['content'][$i].$_GET['content'][$i + 1])));
        }
        fclose($myfile);
}
?>
