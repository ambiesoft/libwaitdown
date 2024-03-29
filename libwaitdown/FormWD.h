#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace libwaitdown {

	/// <summary>
	/// FormWD の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class FormWD : public System::Windows::Forms::Form
	{
	public:
		FormWD(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FormWD()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timerMain;
	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timerMain = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timerMain
			// 
			this->timerMain->Interval = 5000;
			this->timerMain->Tick += gcnew System::EventHandler(this, &FormWD::timerMain_Tick);
			// 
			// FormWD
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 56);
			this->Name = L"FormWD";
			this->Text = L"FormWD";
			this->Load += gcnew System::EventHandler(this, &FormWD::FormWD_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		static void WaitDownloadWindow();
	internal:
		std::vector<HWND>* vWins_;
	protected:
		virtual void OnLoad(EventArgs^ e) override
		{
			Visible = false; 
			ShowInTaskbar = false; 
			Form::OnLoad(e);
		}

	private: System::Void FormWD_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			timerMain->Enabled = true;
			this->Visible = false;
		}
	private: System::Void timerMain_Tick(System::Object^  sender, System::EventArgs^  e) 
		{
			for(std::vector<HWND>::iterator it = vWins_->begin(); it != vWins_->end() ; ++it)
			{
				if(IsWindow(*it) && IsWindowVisible(*it))
				{
					return;
				}
			}
			timerMain->Enabled = false;
			this->Close();
		}
	};
}
