/**
* This file has been modified from its orginal sources.
*
* Copyright (c) 2012 Software in the Public Interest Inc (SPI)
* Copyright (c) 2012 David Pratt
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***
* Copyright (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#ifndef OSX_USER_WINDOW_H
#define OSX_USER_WINDOW_H
namespace ti
{
    class OSXUIBinding;
    class OSXMenuItem;

    class OSXUserWindow : public UserWindow
    {
        public:
            OSXUserWindow(AutoPtr<WindowConfig> config, AutoUserWindow& parent);
            ~OSXUserWindow();

            void OpenChooserDialog(bool files, TiMethodRef callback, bool multiple,
                std::string& title, std::string& path, std::string& defaultName,
                std::vector<std::string>& types, std::string& typesDescription);
            void OpenFileChooserDialog(TiMethodRef callback, bool multiple,
                std::string& title, std::string& path, std::string& defaultName,
                std::vector<std::string>& types, std::string& typesDescription);
            void OpenFolderChooserDialog(TiMethodRef callback, bool multiple,
                std::string& title, std::string& path, std::string& defaultName);
            void OpenSaveAsDialog(TiMethodRef callback, std::string& title,
                std::string& path, std::string& defaultName, std::vector<std::string>& types,
                std::string& typesDescription);
            void Hide();
            void Show();
            void Minimize();
            void Maximize();
            void Unminimize();
            void Unmaximize();
            bool IsMinimized();
            bool IsMaximized();
            void Focus();
            void Unfocus();
            bool IsUsingChrome();
            void SetUsingChrome(bool chrome);
            bool IsUsingScrollbars();
            bool IsFullscreen();
            void Open();
            bool Close();
            double GetX();
            void SetX(double x);
            double GetY();
            void SetY(double y);
            void MoveTo(double x, double y);
            double GetWidth();
            void SetWidth(double width);
            double GetMaxWidth();
            void SetMaxWidth(double width);
            double GetMinWidth();
            void SetMinWidth(double width);
            double GetHeight();
            void SetHeight(double height);
            double GetMaxHeight();
            void SetMaxHeight(double height);
            void ReconfigureWindowConstraints();
            double GetMinHeight();
            void SetMinHeight(double height);
            void SetSize(double width, double height);
            Bounds GetBoundsImpl();
            void SetBoundsImpl(Bounds bounds);
            std::string GetTitle();
            void SetTitleImpl(const std::string& title);
            std::string GetURL();
            void SetURL(std::string& url);
            bool IsResizable();
            void SetResizableImpl(bool resizable);
            bool IsMaximizable();
            void SetMaximizable(bool maximizable);
            bool IsMinimizable();
            void SetMinimizable(bool minimizable);
            bool IsCloseable();
            void SetCloseable(bool closeable);
            bool IsVisible();
            double GetTransparency();
            void SetTransparency(double transparency);
            void SetFullscreen(bool fullscreen);
            bool IsTopMost();
            void SetTopMost(bool topmost);

            void SetMenu(AutoMenu menu);
            AutoMenu GetMenu();
            void SetContextMenu(AutoMenu menu);
            AutoMenu GetContextMenu();
            void SetIcon(std::string& iconPath);
            std::string& GetIcon();

            NativeWindow* GetNative() { return nativeWindow; }
            void Focused();
            void Unfocused();
            virtual void ShowInspector(bool console=false);
            void SetContentsImpl(const std::string&, const std::string&);
            void SetPluginsEnabled(bool enabled);
            
            // Dirty/edited windows are an OSX-specific feature.
            // Corresponds to NSWindow -isDocumentEdited/-setDocumentEdited
            bool IsDocumentEdited();
            void SetDocumentEdited(bool edited);

        private:
            NativeWindow* nativeWindow;
            unsigned int nativeWindowMask;
            bool focused;
            AutoPtr<OSXMenu> menu;
            AutoPtr<OSXMenu> contextMenu;
            AutoPtr<OSXUIBinding> osxBinding;
            static bool initial;
            std::string iconPath;

            NSRect CalculateWindowFrame(double x, double y,
                double width, double height);
            NSScreen* GetWindowScreen();
            DISALLOW_EVIL_CONSTRUCTORS(OSXUserWindow);
    };
}

#endif
