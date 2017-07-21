/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGRAWPRESENTATIONGENERATOR_H
#define RVNGRAWPRESENTATIONGENERATOR_H

#include "librevenge-generators-api.h"

#include <librevenge/librevenge.h>
#include <librevenge-stream/librevenge-stream.h>

namespace librevenge
{

struct RVNGRawPresentationGeneratorImpl;

class REVENGE_GENERATORS_API RVNGRawPresentationGenerator : public RVNGPresentationInterface
{
	// disable copying
	RVNGRawPresentationGenerator(const RVNGRawPresentationGenerator &other);
	RVNGRawPresentationGenerator &operator=(const RVNGRawPresentationGenerator &other);

public:
	explicit RVNGRawPresentationGenerator(bool printCallgraphScore);
	~RVNGRawPresentationGenerator() override;

	void startDocument(const RVNGPropertyList &propList) override;
	void endDocument() override;
	void setDocumentMetaData(const RVNGPropertyList &propList) override;
	void defineEmbeddedFont(const RVNGPropertyList &propList) override;
	void startSlide(const RVNGPropertyList &propList) override;
	void endSlide() override;
	void startMasterSlide(const RVNGPropertyList &propList) override;
	void endMasterSlide() override;
	void setSlideTransition(const RVNGPropertyList &propList) override;
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
	void insertText(const RVNGString &str) override;
	void insertLineBreak() override;

	void insertField(const RVNGPropertyList &propList) override;

	void openOrderedListLevel(const RVNGPropertyList &propList) override;
	void openUnorderedListLevel(const RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;
	void closeUnorderedListLevel() override;
	void openListElement(const RVNGPropertyList &propList) override;
	void closeListElement() override;

	void startTableObject(const RVNGPropertyList &propList) override;
	void openTableRow(const RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const RVNGPropertyList &propList) override;
	void endTableObject() override;

	void startComment(const RVNGPropertyList &propList) override;
	void endComment() override;

	void startNotes(const RVNGPropertyList &propList) override;
	void endNotes() override;

	void defineChartStyle(const RVNGPropertyList &propList) override;
	void openChart(const RVNGPropertyList &propList) override;
	void closeChart() override;
	void openChartTextObject(const RVNGPropertyList &propList) override;
	void closeChartTextObject() override;
	void openChartPlotArea(const RVNGPropertyList &propList) override;
	void closeChartPlotArea() override;
	void insertChartAxis(const RVNGPropertyList &propList) override;
	void openChartSeries(const librevenge::RVNGPropertyList &propList) override;
	void closeChartSeries() override;

	void openAnimationSequence(const RVNGPropertyList &propList) override;
	void closeAnimationSequence() override;
	void openAnimationGroup(const RVNGPropertyList &propList) override;
	void closeAnimationGroup() override;
	void openAnimationIteration(const RVNGPropertyList &propList) override;
	void closeAnimationIteration() override;
	void insertMotionAnimation(const RVNGPropertyList &propList) override;
	void insertColorAnimation(const RVNGPropertyList &propList) override;
	void insertAnimation(const RVNGPropertyList &propList) override;
	void insertEffect(const RVNGPropertyList &propList) override;

private:
	RVNGRawPresentationGeneratorImpl *m_impl;
};

}

#endif // RVNGRAWPRESENTATIONGENERATOR_H

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
