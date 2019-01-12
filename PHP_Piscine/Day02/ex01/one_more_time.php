#!/usr/bin/php
<?php 
$months = array("Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
"Aout", "Septembre", "Octobre", "Novembre", "Decembre", "");
$days = array("Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche", "");
$day_month = array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
try{
$line = $argv[1];
$keywords = preg_split("/[\s,]+/", $line, -1, PREG_SPLIT_NO_EMPTY);


//Check for correct month
$month = 1;
foreach ($months as &$val)
{
    if ($val == $keywords[2])
        break;
    $month++;
}
unset($val);
//Check for correct day
$day = 0;
foreach ($days as &$val)
{
    if ($val == $keywords[0])
        break;
    $day++;
}


$d1 = new DateTime("{$keywords[3]}-{$month}-{$keywords[1]} {$keywords[4]}");
$d2 = new DateTime("1970-01-01 00:00:00");
$interval = $d2->diff($d1);
$s = $interval->format('%s');
$d = $interval->format('%a');
$m = $interval->format('%i');
$h = $interval->format('%h');
$M = $interval->format('%m');
$y = $interval->format('%y');
$answer = (86400 * $d) + (60 * $m) + (3600 * $h) + $s - 3600;
if (is_numeric($answer))
    printf("%d\n",$answer);
else
    printf("Wrong Format\n");
}
catch(Exception $e)
{
    printf("Wrong Format\n");
}

?>