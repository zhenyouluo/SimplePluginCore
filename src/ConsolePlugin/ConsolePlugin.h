﻿/** \file ConsolePlugin.h
    \brief Интерактивная консоль
    \details
    \todo
    - Нужен метод для добавления плагинами собственных комманд в консоль \n
    -- например, менеджер плагинов может ввести обработчик для комманды
    <tt>version "PluginName", update, etc</tt> \n
    -- сетевой модуль <tt>download, connect, etc...</tt> \n
    По сути это консольный алиас на метод.
*/
#pragma once

#include "../Core/PluginInterface.h"
#include <QObject>
#include <QHash>

//===============================================================
/// Консоль для непосредственного управления
class ConsolePlugin: public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

    // реализация виртуальных методов интерфейса
    const QString getPluginId() const;
    const long Version() const;
    QByteArray CallInternal(const QByteArray& methodName, QByteArray &param);
protected:
    QStringList getMethodList() const;

    /// Приглашение ввода \'\>\>\'
    QString prompt;

    /// Запускает консоль
    QByteArray StartConsole();
    /// Инициализация внутренних переменных
    void InitializeConsole();

    /// Показывает приглашение и некую информацию о консоли
    void ShowWelcome();

    /** Обработчик вводимых комманд
    */
    bool CommandProcessor(QString& commandList);

    /** Создает синоним к длинному имени функции или выводит список текущих
        \details Синонимы предназначены для сокращения длинных имен методов.
            Как следствие, их можно использовать в качестве комманд консоли,
            вместо полной формы \n
            <tt>call Plugin.Func param =>> FuncAlias param</tt>\n
        \par Пример создания синонима для Basic.echo
        \code
                >>echo
                METHOD echo DOESN`T FOUND

                >>alias echo Basic.echo
                echo    Basic.echo

                >>alias
                Current aliases list:
                echo    Basic.echo

                >>echo fegre
                fegre+fegre

        \endcode
        \param param Метод принимает описание синонима в следующем виде:\n
        - Слово-синоним вызываемой функции
        - Имя сопоставляемого метода\n
        Если параметр NULL то выводит список созданных синонимов
        \note парсим следующим RegExp <tt>"(\w+)\s(\w+\.\w+)"</tt> где
            \\1 синоним,
            \\2 Имя сопоставляемого метода.
    */
    void createAlias(QByteArray& param);

    /// Выводит список всех синонимов
    QByteArray listAliases();

    /** Вызов метода, в том числе по синониму
        \details Вызывает метод, подставляя название вместо синонима,
        если необходимо
        \param param Коммандная строка полностью
      */
    void resolveCall(QString &param);

    /// Хранит список синонимов методов
    QHash<QString, QString> aliases;
};
//===============================================================
