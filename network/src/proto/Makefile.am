noinst_PROGRAMS = #encode decode

asn:
	snacc -C -u /usr/include/snacc/asn1/asn-useful.asn1 RainbruRPG.asn

clean-local:
	rm -fr RainbruRPG.h RainbruRPG.C *~

.PHONY: asn

all-local: asn
