BEGIN { FS="::"; conta=0 }
/<[a-zA-Z\d]+>/ { conta++; print $1 " -> " $2 " -> " $(NF-1) } 
END { print conta " - " NR " = " conta/NR }