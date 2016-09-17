#include "snowuptimemonitor.h"
#include "pingsnow.h"
#include "sendemail.h"
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	SnowUptimeMonitor::SnowUptimeMonitorForm form;
	Application::Run(%form);
}
