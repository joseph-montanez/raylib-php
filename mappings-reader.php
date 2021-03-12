<?php

$row = 1;
$mapped = 0;
$todo = 0;
$skipped = 0;
$total = 0;

echo "# raylib to PHP Mapping / Progress

This is a one to one mapping of each raylib function.\n\n";

if (($handle = fopen(__DIR__ . '/raylib-3.5-status-functions.csv', "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 5000, ",")) !== FALSE) {
        if ($row === 1) {
            $header = $data;
            $row++;
            continue;
        }

        $mapped_data = [];

        $num = count($data);
        $row++;
        for ($c=0; $c < $num; $c++) {
            $mapped_data[$header[$c]] = $data[$c];
        }

        if (stristr($mapped_data['Function'], ';') !== false) {
            if ($mapped_data['Mapped Method'] === '--') { $skipped++; }
            elseif (strtoupper($mapped_data['Mapped Method']) === 'TODO') { $todo++; }
            else { $mapped++; }
            $total++;

            echo '| ' . $mapped_data['Function'] . ' | ' . $mapped_data['Mapped Method'] . ' | ' . $mapped_data['Implementation Comment'] . ' |', PHP_EOL;
        } elseif(stristr($mapped_data['Function'], ';') === false && strlen($mapped_data['Function']) > 0) {
            echo PHP_EOL . PHP_EOL;
            echo '##' . $mapped_data['Function'], PHP_EOL . PHP_EOL;
            echo '| C API | PHP API | Comment |', PHP_EOL;
            echo '|-------|---------|---------|', PHP_EOL;
        }

    }
    fclose($handle);

    echo "\nTotal: {$total}
Wont Implement: {$skipped}
Todo: {$todo}
Mapped: {$mapped}";

    echo "\nDone: " . round($mapped / ($total - $skipped) * 100) . '%';
}
?>