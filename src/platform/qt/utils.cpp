/* Copyright (c) 2013-2017 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "utils.h"

#include <mgba/core/version.h>

#include <QCoreApplication>
#include <QObject>

namespace QGBA {

QString niceSizeFormat(size_t filesize) {
	double size = filesize;
	QString unit = QObject::tr("%1 byte");
	if (size >= 1024.0) {
		size /= 1024.0;
		unit = QObject::tr("%1 kiB");
	}
	if (size >= 1024.0) {
		size /= 1024.0;
		unit = QObject::tr("%1 MiB");
	}
	return unit.arg(size, 0, 'f', int(size * 10) % 10 ? 1 : 0);
}

QString nicePlatformFormat(mPlatform platform) {
	switch (platform) {
#ifdef M_CORE_GBA
	case mPLATFORM_GBA:
		return QObject::tr("GBA");
#endif
#ifdef M_CORE_GB
	case mPLATFORM_GB:
		return QObject::tr("GB");
#endif
	default:
		return QObject::tr("?");
	}
}

bool convertAddress(const QHostAddress* input, Address* output) {
	if (input->isNull()) {
		return false;
	}
	Q_IPV6ADDR ipv6;
	switch (input->protocol()) {
	case QAbstractSocket::IPv4Protocol:
		output->version = IPV4;
		output->ipv4 = input->toIPv4Address();
		break;
	case QAbstractSocket::IPv6Protocol:
		output->version = IPV6;
		ipv6 = input->toIPv6Address();
		memcpy(output->ipv6, &ipv6, 16);
		break;
	default:
		return false;
	}
	return true;
}

QString romFilters(bool includeMvl) {
	QStringList filters;
	QStringList formats;

#ifdef M_CORE_GBA
	QStringList gbaFormats{
		"*.gba",
#if defined(USE_LIBZIP) || defined(USE_MINIZIP)
		"*.zip",
#endif
#ifdef USE_LZMA
		"*.7z",
#endif
#ifdef USE_ELF
		"*.elf",
#endif
		"*.agb",
		"*.mb",
		"*.rom",
		"*.bin"};
	formats.append(gbaFormats);
	filters.append(QCoreApplication::translate("QGBA", "Game Boy Advance ROMs (%1)", nullptr).arg(gbaFormats.join(QChar(' '))));
#endif

#ifdef M_CORE_DS
	QStringList dsFormats{
		"*.nds",
		"*.srl",
#if defined(USE_LIBZIP) || defined(USE_ZLIB)
		"*.zip",
#endif
#ifdef USE_LZMA
		"*.7z",
#endif
		"*.rom",
		"*.bin"};
	formats.append(dsFormats);
	filters.append(QCoreApplication::translate("QGBA", "DS ROMs (%1)").arg(dsFormats.join(QChar(' '))));
#endif

#ifdef M_CORE_GB
	QStringList gbFormats{
		"*.gb",
		"*.gbc",
		"*.sgb",
#if defined(USE_LIBZIP) || defined(USE_MINIZIP)
		"*.zip",
#endif
#ifdef USE_LZMA
		"*.7z",
#endif
		"*.rom",
		"*.bin"};
	formats.append(gbFormats);
	filters.append(QCoreApplication::translate("QGBA", "Game Boy ROMs (%1)", nullptr).arg(gbFormats.join(QChar(' '))));
#endif

	formats.removeDuplicates();
	filters.prepend(QCoreApplication::translate("QGBA", "All ROMs (%1)", nullptr).arg(formats.join(QChar(' '))));
	if (includeMvl) {
		filters.append(QCoreApplication::translate("QGBA", "%1 Video Logs (*.mvl)", nullptr).arg(projectName));
	}
	return filters.join(";;");
}

}
