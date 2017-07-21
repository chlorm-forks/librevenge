/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGSTREAMIMPLEMENTATION_H
#define RVNGSTREAMIMPLEMENTATION_H

#include "librevenge-stream-api.h"

#include "RVNGStream.h"

namespace librevenge
{

class RVNGFileStreamPrivate;

class REVENGE_STREAM_API RVNGFileStream: public RVNGInputStream
{
public:
	explicit RVNGFileStream(const char *filename);
	~RVNGFileStream() override;

	const unsigned char *read(unsigned long numBytes, unsigned long &numBytesRead) override;
	long tell() override;
	int seek(long offset, RVNG_SEEK_TYPE seekType) override;
	bool isEnd() override;

	bool isStructured() override;
	unsigned subStreamCount() override;
	const char *subStreamName(unsigned id) override;
	bool existsSubStream(const char *name) override;
	RVNGInputStream *getSubStreamById(unsigned id) override;
	RVNGInputStream *getSubStreamByName(const char *name) override;

private:
	RVNGFileStreamPrivate *d;
	RVNGFileStream(const RVNGFileStream &); // copy is not allowed
	RVNGFileStream &operator=(const RVNGFileStream &); // assignment is not allowed
};

class RVNGStringStreamPrivate;

class REVENGE_STREAM_API RVNGStringStream: public RVNGInputStream
{
public:
	RVNGStringStream(const unsigned char *data, const unsigned int dataSize);
	~RVNGStringStream() override;

	const unsigned char *read(unsigned long numBytes, unsigned long &numBytesRead) override;
	long tell() override;
	int seek(long offset, RVNG_SEEK_TYPE seekType) override;
	bool isEnd() override;

	bool isStructured() override;
	unsigned subStreamCount() override;
	const char *subStreamName(unsigned) override;
	bool existsSubStream(const char *name) override;
	RVNGInputStream *getSubStreamByName(const char *name) override;
	RVNGInputStream *getSubStreamById(unsigned) override;

private:
	RVNGStringStreamPrivate *d;
	RVNGStringStream(const RVNGStringStream &); // copy is not allowed
	RVNGStringStream &operator=(const RVNGStringStream &); // assignment is not allowed
};

}

#endif // RVNGSTREAMIMPLEMENTATION_H
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
