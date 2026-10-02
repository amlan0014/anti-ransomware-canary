savedcmd_ransomguard.mod := printf '%s\n'   ransomguard.o | awk '!x[$$0]++ { print("./"$$0) }' > ransomguard.mod
