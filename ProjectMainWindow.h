#ifndef Project_MainWindow_H
#define Project_MainWindow_H

#include "vtkSmartPointer.h"
#include "QMainWindow"
#include "ui_ProjectMainWindow.h"
// Note: ui_NAME.h, the NAME comes from the Widget name from Qt Designer!

class vtkImageViewer2;
class vtkRenderer;
class Ui_ProjectMainWindow;
//class vtkEventQtSlotConnect;
//class vtkCommand;

class ProjectMainWindow : public QMainWindow, private Ui::ProjectMainWindow
{
Q_OBJECT

public:
    ProjectMainWindow();
    ~ProjectMainWindow();

private slots:
    void onOpenSlot();

private:
    vtkSmartPointer<vtkImageViewer2> m_pImageViewer;
    vtkSmartPointer<vtkRenderer> m_pRenderer;

    // Designer Form
    Ui_ProjectMainWindow *ui;
};

#endif