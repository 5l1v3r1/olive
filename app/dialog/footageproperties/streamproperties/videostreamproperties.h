/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef VIDEOSTREAMPROPERTIES_H
#define VIDEOSTREAMPROPERTIES_H

#include <QCheckBox>
#include <QComboBox>
#include <QUndoCommand>

#include "project/item/footage/videostream.h"
#include "streamproperties.h"

class VideoStreamProperties : public StreamProperties
{
public:
  VideoStreamProperties(VideoStreamPtr stream);

  virtual void Accept(QUndoCommand* parent) override;

private:
  /**
   * @brief Attached video stream
   */
  VideoStreamPtr stream_;

  /**
   * @brief Setting for associated/premultiplied alpha
   */
  QCheckBox* video_premultiply_alpha_;

  /**
   * @brief Setting for this media's color space
   */
  QComboBox* video_color_space_;

  class VideoStreamChangeCommand : public QUndoCommand {
  public:
    VideoStreamChangeCommand(VideoStreamPtr stream,
                             bool premultiplied,
                             QString colorspace,
                             QUndoCommand* parent = nullptr);

    virtual void redo() override;
    virtual void undo() override;

  private:
    VideoStreamPtr stream_;

    bool new_premultiplied_;
    QString new_colorspace_;

    bool old_premultiplied_;
    QString old_colorspace_;
  };
};

#endif // VIDEOSTREAMPROPERTIES_H
