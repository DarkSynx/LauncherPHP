echo "hello world!";
echo "hello world!";
echo "hello world!";
echo "hello world!";
$fp = fopen('test.txt', 'w');
fwrite($fp, "hello world!");
fclose($fp);
sleep(10);