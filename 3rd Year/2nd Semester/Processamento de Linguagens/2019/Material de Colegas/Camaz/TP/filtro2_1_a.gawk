BEGIN { FS="::"; conta=0 }
/^Beira L/ { conta++; print $1 " -> " $2 " -> " $NF } 
END { print conta " - " NR " = " conta/NR }