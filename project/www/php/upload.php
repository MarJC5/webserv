<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8" />
    <title>Webserv - POST</title>
    <link rel="apple-touch-icon" sizes="180x180" href="/public/favicon/apple-touch-icon.png">
    <link rel="icon" type="image/png" sizes="32x32" href="/public/favicon/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="/public/favicon/favicon-16x16.png">
    <link rel="manifest" href="/public/favicon/site.webmanifest">
    <link rel="mask-icon" href="/public/favicon/safari-pinned-tab.svg" color="#373e3e">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="theme-color" content="#ffffff">
    <link rel="stylesheet" href="/src/stylesheets/main.css">
</head>

<body class="post-page">

<header>
    <div class="container grid">
        <h1 class="uppercase">
            <a href="/index.html">Webserv - POST</a>
        </h1>
        <ul class="ul-inline">
            <li><a href="/methods/get.html">Get</a></li>
            <li><a href="/methods/post.html">Post</a></li>
            <li><a href="/methods/delete.html">Delete</a></li>
            <li><a href="/php/index.php">CGI</a></li>
            <li><a href="/uploads">UPLOADS</a></li>
        </ul>
    </div>
</header>

<main>
    <div class="container">
<?php
$target_dir = "../uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

#echo "_FILES<br>";
#echo '<pre>';
#print_r($_FILES);
#echo '</pre>';
#echo "<br><br>_POST<br>";
#echo '<pre>';
#print_r($_POST);
#echo '</pre>';
#echo "<br><br>_ENV<br>";
#echo '<pre>';
#print_r($_ENV);
#echo '</pre>';
#echo "<br><br>";

// Check if file was uploaded successfully
if ($_FILES["fileToUpload"]["error"] == UPLOAD_ERR_OK) {
  // Check if image file is a actual image or fake image
  $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
  if($check !== false) {
    echo "File is an image - " . $check["mime"] . ".";
    echo "<br><br>";
    $uploadOk = 1;
  } else {
    echo "File is not an image.";
    echo "<br><br>";
    $uploadOk = 0;
  }
} else {
  echo "Sorry, there was an error uploading your file.";
  echo "<br><br>";
  $uploadOk = 0;
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 5000000) {
  echo "Sorry, your file is too large.";
  echo "<br><br>";
  $uploadOk = 0;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
  echo "Sorry, your file was not uploaded.";
  echo "<br><br>";
// if everything is ok, try to upload file
} else {
  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    echo "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded.";
    echo "<br><br>";
  } else {
    echo "Sorry, there was an error uploading your file.";
    echo "<br><br>";
  }
}
?>
    </div>
</main>

<footer>
    <div class="container">
        <p>&#169;2023 - Webserv -</p>
        <ul class="authors">
            <li><a href="https://github.com/BolleCola">BolleCola</a></li>
            <li><a href="https://github.com/Tywael">Tywael</a></li>
            <li><a href="https://github.com/MarJC5">MarJC5</a></li>
        </ul>
    </div>
</footer>

</body>
</html>
