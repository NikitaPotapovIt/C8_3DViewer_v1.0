#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "glview.h"
#include "qgifimage.h"
#include "settings.h"

extern "C" {
#include "headers/parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainViewer;
}
QT_END_NAMESPACE

class MainViewer : public QMainWindow {
  Q_OBJECT

 public:
  MainViewer(QWidget *parent = nullptr);
  ~MainViewer();
  void get_settings();

 private slots:
  void on_load_file_clicked();
  void on_translate_clicked();
  void on_rotate_clicked();
  void on_scale_clicked();
  void on_slider_move_x_valueChanged(int value);
  void on_slider_move_y_valueChanged(int value);
  void on_slider_move_z_valueChanged(int value);
  void on_slider_rotation_x_valueChanged(int value);
  void on_slider_rotation_y_valueChanged(int value);
  void on_slider_rotation_z_valueChanged(int value);
  void on_slider_scale_valueChanged(int value);
  void on_settings_clicked();
  void settings_handler();
  void on_screenshot_clicked();
  void on_gif_clicked();
  void saveGifFrame();

 private:
  Ui::MainViewer *ui;
  Settings *settings;
  glView *gl;
  obj_t objMain;
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  int time;
  QString gifSavePath;
  void init_ui();
  void closeEvent(QCloseEvent *event);
  void moveEvent(QMoveEvent *e);
};
#endif  // MAINVIEWER_H
