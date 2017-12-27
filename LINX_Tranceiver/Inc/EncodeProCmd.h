/* Sample C code for encoding Hum-xxx-PRO commands
**
** Copyright 2015 Linx Technologies
** 155 Ort Lane
** Merlin, OR, US 97532
** www.linxtechnologies.com
**
** License:
** Permission is granted to use and modify this code, without royalty, for
** any purpose, provided the copyright statement and license are included.
*/

/* Function: HumProCommand
** Description: This function encodes a command byte sequence.
** If len = 1, a read command is generated.
** If len > 1, a write command is generated.
** rcmd[0] = register number
** rcmd[1..(n-1)] = bytes to write
*/
unsigned char /* number of encoded bytes, n+2 to 2*n+2 */
HumProCommand(
              unsigned char *ecmd, /* out: encoded command, length >= 2*n + 2 */
              const unsigned char *rcmd, /* in: sequence of bytes to encode */
              unsigned char n /* number of bytes in rcmd, 1..32 */
              );


/* Function: HumProRead
** Description: This function encodes a read command to the specified
** register address.
*/
unsigned char /* number of encoded bytes, 3 to 4 */
HumProRead  (
            unsigned char   *cmd,    /* out: encoded read command, length >= 4 */
            unsigned char    reg     /* register number to read, 0..0xff */
            );

/* Function: HumProWrite
** Description: This function encodes a command to write a single byte to
** a specified register address.
*/
unsigned char /* number of encoded bytes, 4 to 6 */
HumProWrite(
            unsigned char  *cmd,    /* out: encoded read command, length >= 6 */
            unsigned char   reg,    /* register number to write, 0..0xff */
            unsigned char   val     /* value byte, 0..0xff */
            );



