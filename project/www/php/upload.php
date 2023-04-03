<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8" />
    <title>Webserv - CGI Upload</title>
</head>

<body class="cgi-page">
<main>
    <div class="container">
<?php
$target_dir = "../uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

echo "_FILES<br>";
echo '<pre>';
print_r($_FILES);
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

// Check if file was uploaded successfully
if ($_FILES["fileToUpload"]["error"] == UPLOAD_ERR_OK) {
  // Check if image file is a actual image or fake image
  $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
  if($check !== false) {
    echo "File is an image - " . $check["mime"] . ".";
    $uploadOk = 1;
  } else {
    echo "File is not an image.";
    $uploadOk = 0;
  }
} else {
  echo "Sorry, there was an error uploading your file.";
  $uploadOk = 0;
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 5000000) {
  echo "Sorry, your file is too large.";
  $uploadOk = 0;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
  echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    echo "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded.";
  } else {
    echo "Sorry, there was an error uploading your file.";
  }
}
?>
    </div>
</main>

</body>
</html>
