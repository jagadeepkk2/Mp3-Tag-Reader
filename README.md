# Mp3-Tag-Reader
MP3 tag reader is a software which will read and display MP3 (ID3) tag
information from MP3 files. The software will be desktop based and not web
based.
About (mp3) ID3 tag
ID3 is a metadata container most often used in conjunction with the MP3
audio file format. It allows information such as the title, artist, album, track
number, and other information about the file to be stored in the file itself.
There are two unrelated versions of ID3: ID3v1 and ID3v2. You will have to
first detect the ID3 version before getting the tag details.
Total 128 bytes used for storing these metadata. If you one sum the the size of
all these fields we see that 30+30+30+4+30+1 equals 125 bytes and not 128
bytes. The missing three bytes can be found at the very end of the tag, before
the song title. These three bytes are always "TAG" and is the identification
that this is indeed a ID3 tag. As all artists doesn't have a 30 character name it
is said that if there is some bytes left after the information is entered in the
field, those bytes should be fille with the binary value 0.
An ID3v2 tag starts with a tag header followed by one or more frames. Each
frame in turn consists of a header and (usually) some kind of content.
The ID3v2 tag is more flexible and hence more difficult to work with. An ID3v2
tag has a signature code of "ID3x" where x is the sub-version number of the
tag. Typically ID3v2 tags are found at the beginning of an MP3 file but this is
not an absolute restriction. What happens next depends on the subversion of
the ID3v2 tag. As far as we can tell, there have been three versions so far: 2,3
and 4.
ID3v2 header
ID3v2/file identifier "ID3"
ID3v2 version$03 00 (2, 3 or 4)
ID3v2 flags%abc00000
ID3v2 size4 * %0xxxxxxx (Total size of ID3 tag)
ID3v2.2 Frame header
Frame ID
$xx xx xx(Three characters)
eg:TAL
Album/Movie/Show title
TOA
Size
Original artist(s)/performer(s)
$xx xx xx(Three characters)
ID3v2.3 or ID3v2.4 Frame header
Frame ID
$xx xx xx xx (Four characters)
eg: TALB
TIT2
Album/Movie/Show title
Title/songname/content description
Size$xx xx xx xx (Four characters)
Flags$xx xx
