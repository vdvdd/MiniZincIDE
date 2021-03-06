/*
 *  Author:
 *     Guido Tack <guido.tack@monash.edu>
 *
 *  Copyright:
 *     NICTA 2013
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QProcess>
#include <QTimer>
#include <QLabel>
#ifdef MINIZINC_IDE_HAVE_WEBENGINE
#include <QWebEngineView>
#else
#include <QWebView>
#endif
#include <QSet>
#include <QTemporaryDir>
#include <QElapsedTimer>
#include <QApplication>
#include <QMap>
#include <QSet>
#include <QFileSystemWatcher>
#include <QNetworkAccessManager>
#include <QSortFilterProxyModel>
#include <QToolButton>
#include <QProgressBar>
#include <QComboBox>
#include <QVersionNumber>

#include "codeeditor.h"
#include "solverdialog.h"
#include "paramdialog.h"
#include "project.h"
#include "htmlwindow.h"
#include "moocsubmission.h"
#include "solverconfiguration.h"

namespace Ui {
class MainWindow;
}

class FindDialog;
class MainWindow;
class QNetworkReply;
class QTextStream;

class IDEStatistics {
public:
    int errorsShown;
    int errorsClicked;
    int modelsRun;
    QStringList solvers;
    QVariantMap toVariantMap(void);
    IDEStatistics(void);
    void init(QVariant v);
    QByteArray toJson(void);
    void resetCounts(void);
};

class IDE : public QApplication {
    Q_OBJECT
public:
    IDE(int& argc, char* argv[]);
    ~IDE(void);
    struct Doc;
    typedef QMap<QString,Doc*> DMap;
    DMap documents;
    typedef QMap<QString,MainWindow*> PMap;
    PMap projects;
    QSet<MainWindow*> mainWindows;

    QStringList recentFiles;
    QStringList recentProjects;

    QSet<QString> modifiedFiles;
    QTimer modifiedTimer;

    IDEStatistics stats;

    MainWindow* lastDefaultProject;
    QMainWindow* cheatSheet;

    QNetworkAccessManager* networkManager;
    QNetworkReply* versionCheckReply;

#ifdef Q_OS_MAC
    QMenuBar* defaultMenuBar;
    QMenu* recentFilesMenu;
    QMenu* recentProjectsMenu;
public slots:
    void recentFileMenuAction(QAction*);
    void recentProjectMenuAction(QAction*);
public:
#endif

    QFileSystemWatcher fsWatch;

    bool hasFile(const QString& path);
    QPair<QTextDocument*,bool> loadFile(const QString& path, QWidget* parent);
    void loadLargeFile(const QString& path, QWidget* parent);
    QTextDocument* addDocument(const QString& path, QTextDocument* doc, CodeEditor* ce);
    void registerEditor(const QString& path, CodeEditor* ce);
    void removeEditor(const QString& path, CodeEditor* ce);
    void renameFile(const QString& oldPath, const QString& newPath);
    QString appDir(void) const;
    static IDE* instance(void);
    QString getLastPath(void);
    void setLastPath(const QString& path);
    void setEditorFont(QFont font);
    void addRecentFile(const QString& file);
    void addRecentProject(const QString& file);
protected:
    bool event(QEvent *);
protected slots:
    void versionCheckFinished(void);
    void newProject(void);
    void openFile(const QString& filename = QString(""));
    void fileModified(const QString&);
    void fileModifiedTimeout(void);
    void handleFocusChange(QWidget*,QWidget*);
public slots:
    void checkUpdate(void);
    void help(void);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class IDE;
public:
    explicit MainWindow(const QString& project = QString());
    explicit MainWindow(const QStringList& files);
    ~MainWindow();

private:
    void init(const QString& project);
    void compileOrRun();
signals:
    /// emitted when compilation and running of a model has finished
    void finished();

public slots:

    void openFile(const QString &path = QString(), bool openAsModified=false, bool focus=true);
    void on_actionStop_triggered();

private slots:

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void tabCloseRequest(int);

    void tabChange(int);

    void on_actionRun_triggered();

    void checkArgs(QString filepath);
    void checkArgsOutput();
    void checkArgsFinished(int exitcode, QProcess::ExitStatus exitstatus);

    void checkModelStarted();
    void checkModelFinished(int exitcode, QProcess::ExitStatus exitstatus);
    void checkModelError(QProcess::ProcessError);

    void readOutput();
    void readRrofileOutput();

    void procFinished(int, bool showTime=true);

    void outputProcFinished(int, bool showTime=true);

    void procError(QProcess::ProcessError);
    void checkArgsError(QProcess::ProcessError);
    void outputProcError(QProcess::ProcessError);

    void on_actionSave_triggered();
    void on_actionQuit_triggered();

    void statusTimerEvent();

    void on_actionCompile_triggered();

    void openCompiledFzn(int);

    void profileCompiledFzn(int);

    void runCompiledFzn(int,QProcess::ExitStatus);

    void on_actionSave_as_triggered();

    void on_actionClear_output_triggered();

    void on_actionBigger_font_triggered();

    void on_actionSmaller_font_triggered();

    void on_actionAbout_MiniZinc_IDE_triggered();

    void errorClicked(const QUrl&);

    void on_actionDefault_font_size_triggered();

    void on_actionManage_solvers_triggered(bool addNew=false);

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

    void on_actionSelect_font_triggered();

    void on_actionGo_to_line_triggered();

    void on_actionShift_left_triggered();

    void on_actionShift_right_triggered();

    void on_actionHelp_triggered();

    void on_actionNew_project_triggered();

    void on_actionSave_project_triggered();

    void on_actionSave_project_as_triggered();

    void on_actionClose_project_triggered();

    void on_actionFind_next_triggered();

    void on_actionFind_previous_triggered();

    void on_actionSave_all_triggered();

    void on_action_Un_comment_triggered();

    void on_actionOnly_editor_triggered();

    void on_actionSplit_triggered();

    void on_actionPrevious_tab_triggered();

    void on_actionNext_tab_triggered();

    void recentFileMenuAction(QAction*);

    void recentProjectMenuAction(QAction*);

    void on_actionHide_tool_bar_triggered();

    void on_actionToggle_profiler_info_triggered();

    void on_actionShow_project_explorer_triggered();

    void activateFileInProject(const QModelIndex&);

    void onProjectCustomContextMenu(const QPoint&);

    void onActionProjectOpen_triggered();

    void onActionProjectRemove_triggered();

    void onActionProjectRename_triggered();

    void onActionProjectRunWith_triggered();

    void onActionProjectAdd_triggered();

    void on_actionNewModel_file_triggered();

    void on_actionNewData_file_triggered();

    void on_actionSubmit_to_MOOC_triggered();

    void fileRenamed(const QString&, const QString&);

    void on_conf_timeLimit_valueChanged(int arg1);

    void onClipboardChanged();

    void editor_cursor_position_changed();

    void showWindowMenu(void);
    void windowMenuSelected(QAction*);
    void closeHTMLWindow(int);
    void on_actionCheat_Sheet_triggered();
    void check_code();

    void on_actionDark_mode_toggled(bool arg1);

    void moocFinished(int);

    void on_defaultBehaviourButton_toggled(bool checked);

    void on_actionEditSolverConfig_triggered();

    void on_conf_solver_conf_currentIndexChanged(int index);

    void on_solverConfigurationSelected(QAction*);

    void on_cloneSolverConfButton_clicked();
    void on_deleteSolverConfButton_clicked();
    void on_renameSolverConfButton_clicked();

    void on_solverConfNameEdit_returnPressed();
    void on_solverConfNameEdit_escPressed();

    void on_conf_default_toggled(bool checked);
    void on_conf_dock_widget_visibilityChanged(bool visible);

    void on_conf_check_solutions_toggled(bool checked);

    void on_b_next_clicked();

    void on_b_prev_clicked();

    void on_b_replacefind_clicked();

    void on_b_replace_clicked();

    void on_b_replaceall_clicked();

    void on_closeFindWidget_clicked();

    void on_find_textEdited(const QString &arg1);

    void on_extraOptionsBox_toggled(bool arg1);

    void on_actionProfile_compilation_triggered();

protected:
    virtual void closeEvent(QCloseEvent*);
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dropEvent(QDropEvent *);
#ifdef Q_OS_MAC
    virtual void paintEvent(QPaintEvent *);
#endif
    bool eventFilter(QObject *, QEvent *);
    void openJSONViewer(void);
    void finishJSONViewer(void);

    SolverConfiguration* getCurrentSolverConfig(void);
    Solver* getCurrentSolver(void);

    void compileAndRun(const QString& modelPath, const QString& additionalCmdlineParams, const QStringList& additionalDataFiles);
public:
    bool runWithOutput(const QString& modelFile, const QString& dataFile, int timeout, QTextStream& outstream);
    void resolve(int htmlWindowIdentifier, const QString &data);
    QString currentSolver(void) const;
    QString currentSolverConfigName(void);
    int addHtmlWindow(HTMLWindow* w);
private:
    Ui::MainWindow *ui;
    CodeEditor* curEditor;
    QString curFilePath;
    int curHtmlWindow;
    QVector<HTMLWindow*> htmlWindows;
    QVector<QString> htmlWindowModels;
    MznProcess* process;
    MznProcess* check_process;
    QString processName;
    QString curModelFilepath;
    CodeEditor* curCheckEditor;
    MznProcess* outputProcess;
    bool processWasStopped;
    int solutionCount;
    int solutionLimit;
    QTimer solutionLimitTimer;
    QVector<QString> hiddenSolutions;
    int curJSONHandler;
    bool inJSONHandler;
    bool isJSONinitHandler;
    QStringList htmlBuffer;
    bool inHTMLHandler {false};
    bool hadNonJSONOutput;
    QVector<QStringList> JSONOutput;
    QTimer* timer;
    QTimer* solverTimeout;
    QTimer* checkTimer;
    int time;
    QElapsedTimer elapsedTime;
    QProgressBar* progressBar;
    QLabel* statusLabel;
    QLabel* statusLineColLabel;
    QFont editorFont;
    bool darkMode;
    QVector<Solver> solvers;
    QString userSolverConfigDir;
    QString userConfigFile;
    QString mznStdlibDir;
    int defaultSolverIdx;
    QString mznDistribPath;
    QString getMznDistribPath(void) const;
    QString currentFznTarget;
    QString currentPathsTarget;
    bool isOptimisation;
    QStringList currentAdditionalDataFiles;
    bool runSolns2Out;
    QTemporaryDir* tmpDir;
    QVector<QTemporaryDir*> cleanupTmpDirs;
    QVector<MznProcess*> cleanupProcesses;
    QTextCursor incrementalFindCursor;
    QString projectPath;
    bool saveBeforeRunning;
    QString compileErrors;
    QString checkArgsStdout;
    ParamDialog* paramDialog;
    enum CompileMode { CM_RUN, CM_COMPILE, CM_PROFILE };
    CompileMode compileMode;
    bool profileInfoVisible;
    int runTimeout;
    QString minizinc_executable;
    QVersionNumber minizinc_version;
    Project project;
    QSortFilterProxyModel* projectSort;
    QMenu* projectContextMenu;
    QAction* projectOpen;
    QAction* projectRemove;
    QAction* projectRename;
    QAction* projectRunWith;
    QAction* projectAdd;
    QString projectSelectedFile;
    QModelIndex projectSelectedIndex;
    int newFileCounter;
    QComboBox* solverConfCombo;
    QAction* fakeRunAction;
    QAction* fakeStopAction;
    QAction* fakeCompileAction;
    QAction* minimizeAction;
    QTextStream* outputBuffer;
    MOOCSubmission* moocSubmission;
    bool processRunning;

    QToolButton* runButton;
    QVector<SolverConfiguration> projectSolverConfigs;
    QVector<SolverConfiguration> builtinSolverConfigs;
    QVector<QPair<SolverFlag,QWidget*>> extraSolverFlags;
    int currentSolverConfig;
    bool renamingSolverConf;

    void createEditor(const QString& path, bool openAsModified, bool isNewFile, bool readOnly=false, bool focus=true);
    enum ConfMode { CONF_CHECKARGS, CONF_COMPILE, CONF_RUN };
    QStringList parseConf(const ConfMode& confMode, const QString& modelFile, bool isOptimisation);
    void saveFile(CodeEditor* ce, const QString& filepath);
    void saveProject(const QString& filepath);
    void loadProject(const QString& filepath);
    void setEditorFont(QFont font);
    void setLastPath(const QString& s);
    QString getLastPath(void);
    QString setElapsedTime();
    void checkMznPath();
    void updateRecentProjects(const QString& p);
    void updateRecentFiles(const QString& p);
    void addFileToProject(bool dznOnly);
    void updateUiProcessRunning(bool pr);
    void highlightPath(QString& path, int index);
    QVector<CodeEditor*> collectCodeEditors(QVector<QStringList>& locs);
    void updateSolverConfigs(void);
    void setCurrentSolverConfig(int idx);
    void find(bool fwd, bool forceNoWrapAround=false);
public:
    void addOutput(const QString& s, bool html=true);
    void openProject(const QString& fileName);
    bool isEmptyProject(void);
    void selectJSONSolution(HTMLPage* source, int n);
    const Project& getProject(void) { return project; }
};

#endif // MAINWINDOW_H
