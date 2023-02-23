<html>

 <head>

 </head>

 <body>
<form action = "<?php print $_SERVER['PHP_SELF'];?>" method = "post">

  Valeur 1:
<input type = "text" name = "val1" size = "10">
  Valeur 2:
<input type = "text" name = "val2" size = "10">

  Opération:
<input type = "radio" name = "operation" value = "add"> Addition
<input type = "radio" name = "operation" value = "sous"> Sustraction
<input type = "radio" name = "operation" value = "mul"> Multiplication
<input type = "radio" name = "operation" value = "div"> Division
<hr />
<input type = "submit" value = "Calculate">
<input type = "reset" value = "Clear"></form>

 </body>

</html>
