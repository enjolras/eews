<html>
<head>
<title>EEWS Test Client</title>
</head>
<body>
<h1>EEWS Test Client</h1>
<h3>Ticket Result Test</h3>
<?php 


if($_REQUEST['reallySubmit']) { 

require_once('XML/Beautifier.php') ;

$client = new SoapClient('eews.wsdl',array('trace' => TRUE)) ;
$client->__setLocation('http://edujudge.tel.uva.es:2288') ;

$params = array('ticket' => $_REQUEST['ticketID']) ;

$response = $client->getTicketResult($params['ticket']) ;

echo '<h4>Request</h4>' ;
echo '<pre style="border-width:1px;border-style:solid;background-color:#ffffcc;">' ;
$fmt = new XML_Beautifier(array( "multilineTags" => true )) ;
echo(str_replace('>','&gt;',str_replace('<','&lt;',$fmt->formatString($client->__getLastRequest())))) ;
echo '</pre>' ;

echo '<h4>Response</h4>' ;
echo '<pre style="border-width:1px;border-style:solid;background-color:#ffcccc;">' ;
print_r($response) ;
echo '</pre>' ;

?>


<?php } else { 
?>
<form action="getTicketResult.php" method="POST">
<input type="hidden" name="reallySubmit" value="1">
Ticket ID: <input type="text" size="32" maxlength="32" name="ticketID"/><br/>
<input type="submit" value="Submit"/>
</form>
<?php } ?>
</body>
</html>
