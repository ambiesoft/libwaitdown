#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace libwaitdown {

	/// <summary>
	/// FormWD �̊T�v
	///
	/// �x��: ���̃N���X�̖��O��ύX����ꍇ�A���̃N���X���ˑ����邷�ׂĂ� .resx �t�@�C���Ɋ֘A�t����ꂽ
	///          �}�l�[�W ���\�[�X �R���p�C�� �c�[���ɑ΂��� 'Resource File Name' �v���p�e�B��
	///          �ύX����K�v������܂��B���̕ύX���s��Ȃ��ƁA
	///          �f�U�C�i�ƁA���̃t�H�[���Ɋ֘A�t����ꂽ���[�J���C�Y�ς݃��\�[�X�Ƃ��A
	///          ���������݂ɗ��p�ł��Ȃ��Ȃ�܂��B
	/// </summary>
	public ref class FormWD : public System::Windows::Forms::Form
	{
	public:
		FormWD(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
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
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
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
