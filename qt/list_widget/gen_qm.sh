ls *.ts | while read ts_file
do
    file=${ts_file%.ts}
    lrelease ${file}.ts -qm ${file}.qm
done

