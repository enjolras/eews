<html>
<head>
<title>EEWS Test Client</title>
</head>
<body>
<h1>EEWS Test Client</h1>
<h3>Submission Test</h3>
<?php 

$client = new SoapClient('eews.wsdl',array('trace' => TRUE)) ;
$client->__setLocation('http://edujudge.tel.uva.es:2288') ;

if($_REQUEST['reallySubmit']) { 

$params = array('language' => $_REQUEST['lang'],
		'plugin' => $_REQUEST['plugin'],
		'lo' => $_REQUEST['loURL'],
		'priority' => 0,
		'code' => 'LALALA') ;

$response = $client->submitCode($params) ;

echo '<pre>' ;
echo(str_replace('>','&gt;',str_replace('<','&lt;',$client->__getLastRequest()))) ;
echo '</pre>' ;

print_r($response) ;

?>


<?php } else { 
$response = $client->__soapCall('getCapabilities',array()) ;
?>
<form action="submit.php" method="POST">
<input type="hidden" name="reallySubmit" value="1">
LO URL: <input type="text" size="32" value="http://lalalalala" name="loURL"/><br/>
Language: <select name="lang">
<?php
foreach($response['languages'] as $lang) {
	echo '<option>'.$lang->uniqid.'</option>' ;
}
?>
</select>
<br/>
Plugin: <select name="plugin">
<?php
foreach($response['plugins'] as $plugin) {
	echo '<option>'.$plugin->uniqid.'</option>' ;
}
?>
</select><br/>
<input type="submit" value="Submit"/>
</form>
<?php } ?>
</body>
</html>
