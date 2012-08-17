﻿/** \file HiveCore.h
  \brief Класс ядра проекта
  \details Функции ложащиеся на ядро:
  - Загрузка/выгрузка плагинов;
  - Межплагиновое взаимодействие.
  */
#pragma once

#include <QMap>
#include <QStringList>

class PluginInterface;

/** \brief Ядро системы
    \details Реализовано паттерном "одиночка".
    Инcтанцирование поизводится через  \ref HiveCore::Instance().
*/
class HiveCore
{
    /** \brief Список указателей на загруженные плагины с импортированными
    методами */
    typedef  QMap<PluginInterface*, QStringList> PluginMap;
public:
    /** \brief Пустой конструктор
    \details По-хорошему нужно сделать его приватным, но Qt не дает мне этого
    \todo пусть бросает исключение, чтоле? Ибо не должно вызываться нигде,
        кроме метода \ref Instance() */
    HiveCore() {}
    virtual ~HiveCore() {}

    /** \brief Создает статический экземпляр класса ядра и возвращает
            указатель на него
    \return Указатель на статический экземпляр ядра */
    static HiveCore* Instance() {
        static HiveCore* coreInstance = new HiveCore();
        return coreInstance;
    }

    /** \brief Загрузка плагинов
    \details Проматривает директорию <i>plugins</i> и пытается загрузить все
        имеющиеся там файлы в качестве плагина.
    \todo Сделать фильтр по типам файлов */
    void loadPlugins();

    /** \brief Вызов импортированной функции по ее имени
      \details Пытается найти переданное имя в списке импортированных функций
            и вызвать, передав необходимые параметры
      \param methodName Полное имя вызываемого метода.
            Например "SomePlugin.SomeMethod"
      \code{.cpp}
        HiveCore* core = HiveCore::Instance();
        QString method("SomePlugin.SomeMethod");
        QByteArray param("Some data");
        QByteArray* result = core->CallPluginMethod(method, &param);
      \endcode
      \todo По-возможности заменить тип параметра methodName на <i>const char*</i>
    */
    QByteArray* CallPluginMethod(const QString& methodName, QByteArray* params);

    const QStringList listLoadedMethods() const;
protected:
    PluginMap methods;

    int LoadPluginContent(QObject* pobj);
    PluginInterface* locateMethod(QString methodName);

private:
    HiveCore(const HiveCore&);
    const HiveCore& operator =(HiveCore&);
};

QByteArray *CallPluginMethod(const QString& methodName, QByteArray *params);
