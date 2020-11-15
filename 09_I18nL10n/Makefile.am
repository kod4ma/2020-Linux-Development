bin_PROGRAMS=binaryguess
pkgdata_DATA=ru/LC_MESSAGES/binaryguess.mo

ru/LC_MESSAGES/binaryguess.mo: binaryguess.po
		mkdir -p `dirname $@`
		msgfmt $< -o $@

binaryguess_ru.po:	binary.pot
		msgmerge -U $@ $<

binary.pot:	binaryguess.pot binaryguess.c
		xgettext -k_ -c binaryguess.c -o binaryguess.new.pot
		cp binaryguess.pot binary.pot
		msgmerge -U binary.pot binaryguess.new.pot

gitclean:	maintainer-clean
	git clean -fd
