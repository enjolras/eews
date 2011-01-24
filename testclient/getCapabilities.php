<html>
<head>
<title>EEWS Test Client</title>
</head>
<body>
<h1>EEWS Test Client</h1>
<h3>getCapabilities SOAP request</h3>
<table width="100%">
<tr><th width="50%">RAW Output</th><th width="50%">Extracted Data</th></tr>
<tr><td>
<pre style="background-color:#ffff88;border-width:1px;border-style:solid;">
<?php
$client = new SoapClient('eews.wsdl') ;
$client->__setLocation('http://edujudge.tel.uva.es:2288') ;
$response = $client->__soapCall('getCapabilities',array()) ;
print_r($response) ;
?>
</pre>
</td>
<td valign="top">
<b>Version:</b>&nbsp;<?php echo $response['version'] ; ?><br/>
<b>Protocol:</b>&nbsp;<?php echo $response['protocol'] ;?><br/>
<b>Version String:</b>&nbsp;<?php echo $response['versionString'] ;?><br/>
<b>Admin Email:</b>&nbsp;<?php echo $response['adminEmail'] ;?><br/>
<b>Languages:</b><br/>
<table style="border-width:1px;border-style:solid;">
<tr><th>UniqID</th><th>Name</th><th>Version</th><th>Description</th></tr>
<?php
foreach($response['languages'] as $lang) {
	echo '<tr>' ;
	echo '<td>' . $lang->uniqid      . '</td>' ;
	echo '<td>' . $lang->name        . '</td>' ;
	echo '<td>' . $lang->version     . '</td>' ;
	echo '<td>' . $lang->description . '</td>' ;
	echo '</tr>' ;
}
?>
</table>
<b>Plugins:</b><br/>
<table style="border-width:1px;border-style:solid;">
<tr><th>UniqID</th><th>Description</th><th>Version</th><th>Status</th></tr>
<?php
foreach($response['plugins'] as $plugin) {
	echo '<tr>' ;
	echo '<td>' . $plugin->uniqid   . '</td>' ;
	echo '<td>' . $plugin->desc     . '</td>' ;
	echo '<td>' . $plugin->version  . '</td>' ;
	echo '<td>' . $plugin->status   . '</td>' ;
	echo '</tr>' ;
}
?>
</td>
</tr>
</table>
</body>
</html>
