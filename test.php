<?php
log_kit::init("factory", "tag_test", 0);
$logger = new logger("bbb");
$time = microtime(true);

for ($i = 0; $i < 20; $i++) {
    $logger->debug("This is a debug test" . $i);
    $logger->info("This is a info test" . $i);
    $logger->warn("This is a warn test" . $i);
    $logger->error("This is a error test" . $i);
}

echo microtime(true) - $time , "\n";
