printf '== %s\n' "$0"
trap "printf '\n'" EXIT

begin() {
	printf '%-40s' "$1"
}

scdoc() {
	./scdoc "$@" 2>&1
}

end() {
	if [ $? -ne "$1" ]
	then
		printf 'FAIL\n'
	else
		printf 'OK\n'
	fi
}
