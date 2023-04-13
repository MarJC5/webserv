<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
    <title>Webserv - CGI Print</title>

</head>

<body class="cgi-page">
<main>
    <div class="container">

<?php
echo "_GET<br>";
echo '<pre>';
print_r($_GET);
echo '</pre>';
echo "<br><br>_POST<br>";
echo '<pre>';
print_r($_POST);
echo '</pre>';
echo "<br><br>_ENV<br>";
echo '<pre>';
print_r($_ENV);
echo '</pre>';
echo "<br><br>";

?>
    </div>
</main>

</body>
</html>
