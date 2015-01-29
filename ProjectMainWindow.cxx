
#include "ProjectMainWindow.h"

#include "QFileDialog"
#include "QDir"

#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkImageViewer2.h"
#include "QVTKWidget.h"
#include "vtkJPEGReader.h"
#include "vtkImageActor.h"
#include "ProjectMainWindow.h"

ProjectMainWindow::ProjectMainWindow() {
    this->ui = new Ui_ProjectMainWindow;
    this->ui->setupUi(this);

    m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    m_pRenderer    = vtkSmartPointer<vtkRenderer>::New();

    // Set up VTK renderer
//    m_QVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderer); // m_QVTKWidget comes from Qt Designer
    this->ui->m_QVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderer);

    this->ui->menubar->setNativeMenuBar(false);

    // Set up action signals and slots
    connect(this->ui->m_OpenAction, SIGNAL(triggered()), this, SLOT(onOpenSlot()));
}

ProjectMainWindow::~ProjectMainWindow() {
}

void ProjectMainWindow::onOpenSlot() {
    QString filter;
    filter = "JPEG image file (*.jpg *.jpeg)";

    QDir dir;
    QString filename = QFileDialog::getOpenFileName(this,
            QString(tr("Open File")), dir.absolutePath(), filter);
    if(filename.isEmpty())
        return;

    // Unicode filename support
    QByteArray ba = filename.toLocal8Bit();
    const char *fileName_str = ba.data();

    // Read JPG image using vtkJPEGReader
    vtkSmartPointer<vtkJPEGReader> reader =
            vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(fileName_str);

    m_pImageViewer->SetInputData(reader->GetOutput());
    m_pImageViewer->UpdateDisplayExtent();
    m_pImageViewer->SetRenderWindow(this->ui->m_QVTKWidget->GetRenderWindow());
    m_pImageViewer->SetRenderer(m_pRenderer);
    m_pImageViewer->SetupInteractor(this->ui->m_QVTKWidget->GetRenderWindow()->GetInteractor());
    m_pImageViewer->SetSliceOrientationToXY();
    m_pImageViewer->GetImageActor()->InterpolateOff();
    m_pRenderer->ResetCamera();
    m_pRenderer->DrawOn();
    this->ui->m_QVTKWidget->GetRenderWindow()->Render();

}