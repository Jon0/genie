/*
 * GameData.cpp
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/mman.h>
#include <fcntl.h>
#include "GameData.h"

namespace std {

GameData::GameData() {
	FILE *file1 = fopen ("empires2_x1_p1.dat", "rb");
	//SET_BINARY_MODE(file);

	decompress(file1);
}

int GameData::decompress(FILE *source) {
	//printf("begin decompression\n");

	//int ret;
	//z_stream strm;
	//unsigned have;
	//unsigned char in[CHUNK];
	//unsigned char out[CHUNK];

	///* allocate inflate state */
	//strm.zalloc = Z_NULL;
	//strm.zfree = Z_NULL;
	//strm.opaque = Z_NULL;
	//strm.avail_in = 0;
	//strm.next_in = Z_NULL;
	//ret = inflateInit2(&strm, -15); //16+MAX_WBITS
	//if (ret != Z_OK) {
	//	return ret;
	//}

	///* decompress until deflate stream ends or end of file */
	//do {
	//	strm.avail_in = fread(in, 1, CHUNK, source);
	//	// printf("available bytes = %d\n", strm.avail_in);

	//	// check errors
	//	if (ferror (source)) {
	//		// printf("source error\n");
	//		(void) inflateEnd(&strm);
	//		return Z_ERRNO;
	//	}
	//	if (strm.avail_in == 0) {
	//		// printf("error\n");
	//		break;
	//	}

	//	strm.next_in = in;

	//	/* run inflate() on input until output buffer not full */
	//	do {
	//		strm.avail_out = CHUNK;
	//		strm.next_out = out;

	//		ret = inflate(&strm, Z_NO_FLUSH);
	//		assert(ret != Z_STREAM_ERROR); /* state not clobbered */
	//		switch (ret) {
	//		case Z_NEED_DICT:
	//			ret = Z_DATA_ERROR; /* and fall through */
	//		case Z_DATA_ERROR:
	//		case Z_MEM_ERROR:
	//			(void) inflateEnd(&strm);
	//			printf("error %d\n", ret);
	//			return ret;
	//		}

	//		have = CHUNK - strm.avail_out;

	//		// write to buffer
	//		for (int i = 0; i < have; ++i) {
	//			data.push_back(out[i]);
	//		}
	//		//if (fwrite(out, 1, have, dest) != have || ferror(source)) {
	//		//	(void) inflateEnd(&strm);
	//		//	return Z_ERRNO;
	//		//}
	//		//ioBuf.write((char *)&out, have);
	//		//cout.write((char *) &out, have);

	//	} while (strm.avail_out == 0);

	//	/* done when inflate() says it's done */
	//} while (ret != Z_STREAM_END);

	////is = &ioBuf;

	///* clean up and return */
	//(void) inflateEnd(&strm);
	//return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;

	return 0;
}

GameData::~GameData() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
