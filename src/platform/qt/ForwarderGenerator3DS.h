/* Copyright (c) 2013-2022 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#pragma once

#include "ForwarderGenerator.h"

namespace QGBA {

class ForwarderGenerator3DS final : public ForwarderGenerator {
Q_OBJECT

public:
	ForwarderGenerator3DS();

	QList<QPair<QString, QSize>> imageTypes() const override;
	System system() const override { return System::N3DS; }
	QString extension() const override { return QLatin1String("cia"); }

	bool rebuild(const QString& source, const QString& target) override;
};

}
