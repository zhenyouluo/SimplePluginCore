﻿/** \file BasicPlugin.h
\brief Интерфейс плагина
\details */
#pragma once

#include "../Core/PluginInterface.h"
#include <QObject>

//===============================================================
/** \brief Реализация интерфейсов для конкретного плагина */
class BasicPlugin: public QObject, public PluginInterface
{
    Q_OBJECT
    /** \brief указывает компилятору, что этот класс является интерфейсом
            плагина */
    Q_INTERFACES(PluginInterface)

    // реализация виртуальных методов интерфейса
    const QString getPluginId() const;
    const long Version() const;
    QByteArray CallInternal(const QByteArray& methodName, QByteArray& param);
protected:
    QStringList getMethodList() const;

    // собственно полезная нагрузка. Реализацию экспортируемых методов,
    // для удобства, рекомендуется выносить в отдельный файл
    /** \brief Пример обычного метода */
    QByteArray Duplicate(QByteArray &one);
    /** \brief Пример метода, имитируюшего вызов метода из другого плагина */
    QByteArray More(QByteArray &str);
    /** \brief Пример метода не принимающего параметры */
    QByteArray FunctionWithoutParams(void);
};
//===============================================================
