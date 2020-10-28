# SHA256

## Description
- *main.c* - provides a command line user interface;
- *sha256.h, sha256.c* - contains the main part of SHA 256 alghorithm, fully compliant to standard: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
- *static.h, static.c* - contains the static part of algorithm (e.g. *K256, init hash ...*);
- *types.h* - contains typedef aliases;
- *util.h, util.c* - contains utility methods (e.g. *rotl, rotr ...*);

### Unit tests:
- *sha_256.c* - sha 256 test set;
