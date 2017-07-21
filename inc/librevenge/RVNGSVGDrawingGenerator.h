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
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGSVGDRAWINGGENERATOR_H
#define RVNGSVGDRAWINGGENERATOR_H

#include "librevenge-api.h"

#include "RVNGDrawingInterface.h"
#include "RVNGStringVector.h"

namespace librevenge
{

struct RVNGSVGDrawingGeneratorPrivate;

class REVENGE_API RVNGSVGDrawingGenerator : public RVNGDrawingInterface
{
public:
	RVNGSVGDrawingGenerator(RVNGStringVector &vec, const RVNGString &nmspace);
	~RVNGSVGDrawingGenerator() override;

	void startDocument(const RVNGPropertyList &propList) override;
	void endDocument() override;
	void setDocumentMetaData(const RVNGPropertyList &propList) override;
	void defineEmbeddedFont(const RVNGPropertyList &propList) override;
	void startPage(const RVNGPropertyList &propList) override;
	void endPage() override;
	void startMasterPage(const RVNGPropertyList &propList) override;
	void endMasterPage() override;
	void startLayer(const RVNGPropertyList &propList) override;
	void endLayer() override;
	void startEmbeddedGraphics(const RVNGPropertyList &propList) override;
	void endEmbeddedGraphics() override;

	void openGroup(const RVNGPropertyList &propList) override;
	void closeGroup() override;

	void setStyle(const RVNGPropertyList &propList) override;

	void drawRectangle(const RVNGPropertyList &propList) override;
	void drawEllipse(const RVNGPropertyList &propList) override;
	void drawPolyline(const RVNGPropertyList &propList) override;
	void drawPolygon(const RVNGPropertyList &propList) override;
	void drawPath(const RVNGPropertyList &propList) override;
	void drawGraphicObject(const RVNGPropertyList &propList) override;
	void drawConnector(const RVNGPropertyList &propList) override;
	void startTextObject(const RVNGPropertyList &propList) override;
	void endTextObject() override;

	void startTableObject(const RVNGPropertyList &propList) override;
	void openTableRow(const RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const RVNGPropertyList &propList) override;
	void endTableObject() override;

	void openOrderedListLevel(const RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;

	void openUnorderedListLevel(const RVNGPropertyList &propList) override;
	void closeUnorderedListLevel() override;
	void openListElement(const RVNGPropertyList &propList) override;
	void closeListElement() override;

	void defineParagraphStyle(const RVNGPropertyList &propList) override;
	void openParagraph(const RVNGPropertyList &propList) override;
	void closeParagraph() override;

	void defineCharacterStyle(const RVNGPropertyList &propList) override;
	void openSpan(const RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const RVNGPropertyList &propList) override;
	void closeLink() override;

	void insertTab() override;
	void insertSpace() override;
	void insertText(const RVNGString &text) override;
	void insertLineBreak() override;
	void insertField(const RVNGPropertyList &propList) override;

private:
	RVNGSVGDrawingGenerator(const RVNGSVGDrawingGenerator &);
	RVNGSVGDrawingGenerator &operator=(const RVNGSVGDrawingGenerator &);
	RVNGSVGDrawingGeneratorPrivate *m_pImpl;
};

}

#endif // RVNGSVGDRAWINGGENERATOR_H

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
