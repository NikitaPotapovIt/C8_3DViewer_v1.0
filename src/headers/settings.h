#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QSettings>
#include <QWidget>

namespace Ui {
class Settings;
}  // namespace Ui

class Settings : public QWidget {
  Q_OBJECT

 public:
  explicit Settings(QWidget *parent = nullptr);
  ~Settings();
  Ui::Settings *ui;
  QSettings *settings;
  void load_settings();
  void save_settings();

 public slots:
  void on_set_apply_clicked();

 private slots:
  void on_vertex_size_decr_clicked();
  void on_vertex_size_incr_clicked();
  void on_edge_width_decr_clicked();
  void on_edge_width_incr_clicked();
  void on_set_cancel_clicked();
  void on_set_default_clicked();
  void set_default_settings();

 private:
  QString config_file;
};

#endif  // SETTINGS_H
