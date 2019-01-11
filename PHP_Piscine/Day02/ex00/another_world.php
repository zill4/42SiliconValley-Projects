#!/usr/bin/php
<?php 
$line = $argv[1];
$line = trim(preg_replace('/\s+/', ' ', $line));
printf("%s\n",$line);
?>