/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
* Copyright (C) 2002 William Lachance (wrlach@gmail.com)
* Copyright (C) 2002-2003 Marc Maurer (uwog@uwog.net)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
*/

#ifndef RVNGTEXTTEXTGENERATOR_H
#define RVNGTEXTTEXTGENERATOR_H

#include "librevenge-generators-api.h"

#include <librevenge/librevenge.h>
#include <librevenge-stream/librevenge-stream.h>

namespace librevenge
{

struct RVNGTextTextGeneratorImpl;

class REVENGE_GENERATORS_API RVNGTextTextGenerator : public RVNGTextInterface
{
	// disable copying
	RVNGTextTextGenerator(const RVNGTextTextGenerator &other);
	RVNGTextTextGenerator &operator=(const RVNGTextTextGenerator &other);

public:
	explicit RVNGTextTextGenerator(RVNGString &document, const bool isInfo=false);
	~RVNGTextTextGenerator() override;

	void setDocumentMetaData(const RVNGPropertyList &propList) override;

	void startDocument(const RVNGPropertyList &propList) override;
	void endDocument() override;

	void defineEmbeddedFont(const RVNGPropertyList &propList) override;

	void definePageStyle(const RVNGPropertyList &) override;
	void openPageSpan(const RVNGPropertyList &propList) override;
	void closePageSpan() override;
	void openHeader(const RVNGPropertyList &propList) override;
	void closeHeader() override;
	void openFooter(const RVNGPropertyList &propList) override;
	void closeFooter() override;

	void defineSectionStyle(const RVNGPropertyList &) override;
	void openSection(const RVNGPropertyList &propList) override;
	void closeSection() override;

	void defineParagraphStyle(const RVNGPropertyList &) override;
	void openParagraph(const RVNGPropertyList &propList) override;
	void closeParagraph() override;

	void defineCharacterStyle(const RVNGPropertyList &) override;
	void openSpan(const RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const RVNGPropertyList &propList) override;
	void closeLink() override;

	void insertTab() override;
	void insertText(const RVNGString &text) override;
	void insertSpace() override;
	void insertLineBreak() override;
	void insertField(const RVNGPropertyList &propList) override;

	void openOrderedListLevel(const RVNGPropertyList &propList) override;
	void openUnorderedListLevel(const RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;
	void closeUnorderedListLevel() override;
	void openListElement(const RVNGPropertyList &propList) override;
	void closeListElement() override;

	void openFootnote(const RVNGPropertyList &propList) override;
	void closeFootnote() override;
	void openEndnote(const RVNGPropertyList &propList) override;
	void closeEndnote() override;
	void openComment(const RVNGPropertyList &propList) override;
	void closeComment() override;
	void openTextBox(const RVNGPropertyList &propList) override;
	void closeTextBox() override;

	void openTable(const RVNGPropertyList &propList) override;
	void openTableRow(const RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const RVNGPropertyList &propList) override;
	void closeTable() override;

	void openFrame(const RVNGPropertyList &propList) override;
	void closeFrame() override;

	void openGroup(const librevenge::RVNGPropertyList &propList) override;
	void closeGroup() override;

	void defineGraphicStyle(const librevenge::RVNGPropertyList &propList) override;
	void drawRectangle(const librevenge::RVNGPropertyList &propList) override;
	void drawEllipse(const librevenge::RVNGPropertyList &propList) override;
	void drawPolygon(const librevenge::RVNGPropertyList &propList) override;
	void drawPolyline(const librevenge::RVNGPropertyList &propList) override;
	void drawPath(const librevenge::RVNGPropertyList &propList) override;
	void drawConnector(const RVNGPropertyList &propList) override;

	void insertBinaryObject(const RVNGPropertyList &propList) override;
	void insertEquation(const RVNGPropertyList &propList) override;

private:
	RVNGTextTextGeneratorImpl *m_impl;
};

}

#endif /* RVNGTEXTTEXTGENERATOR_H */

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
