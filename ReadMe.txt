+//////////////////////////A6S3��s����/////////////////////////
+V0.1B
+1.��ErrorCode �ɻ�
+
+V0.1A~
+1.�⴫RemoteControl �}Port �q�T�h
+2.�s�WParser3111 ���R�O�B�z�h
+3.Include ���F��]��ۤv����Ƨ���
+
+
+////////////////////Ken ��s����////////////////////////////////

V1.0
1: Origneal Version

V1.0Aa
1: �ץ� Access Level�n�J�v��,�p�G���UCancel�|���~�n�JSuper User���v��
2: �ץ� Interface �bSend Start Delay�p�G��J0�ɭP�L�k�x�s�����D, �åB�W�[���ܵ���
3: �ץ� Run Page Tips, ���� Catoregy ���~�r��
4: �W�[ Test Site Vacc �\��, ���ϥΪ̥i�H�����αҰʴ��մ������� Vacuum

V1.0Ab
1: Offset�W�[�������\��,������r�ɮצb\System\3111.OfNote
2: Setup Page, TrayMap Setting �ܧ��r�� Tray Map Setting
3: Setup Page, IO Montior �ץ��� IO Monitor
4: Setup Pagem Tray Map Setting���, �������D��Input / Output Tray�קאּ Tray Map Setting
5: Manaul Contact, TS Offset �����D�W�[��� (mm)
6: Manual Contact,�bEnable Manual Contact�W�[Test Site Direct Contact �ﶵ,Enable��,�bManual Contact�|�X�{
Contact�Ҧ����,�i�H���Shuttle Input�J��,�άO�������Soaket
7: Manual Contact,�bEnable Manual Contact�W�[Test Site Vacc�\�� �ﶵ,Enable��,
�bManual Contact�|�X�{Ts Vacc�Ҧ��i�H���, �p�G����,����p�G��Shuttle�J��,�h�|����Vacc,�קKVacc�Ӥj�n������
8: Shuttle �W�[�J���ˬd, ��Shuttle ���ʨ�J�ư�(TestSite)�U��,�A�ˬd�@��Jam sensor, �קK���ʪ��L�{��IC Jam, 
�ɭP Wrokpress ���aIC, TestSite Skip �|���s�J��, ��ErrorCode �� 605 Shuttle Input Jam
9: Tray File �����D���� List, �קאּ Tray File
10:Tray File �ק� Base File ������
11:�bRun Page �p�G�bDevice Setup��nTrayFile,���O�٨S�إ߷s���u��,����i�H�����Ѩt�μҦ�����r���
�I�����Mode
12:Test Site Remain IC�i�H��Debug Function�Ψӳ]�w�ӫȤ�O�_�ݭn�Ұʸӥ\��
13:Shuttle Jam Log, �p�G�bShuttle ���ʨ� Test Site �U�診��N�|Log, _ShuttleJam.txt

V1.0Ac
1: Device Setup, TrayFile�קאּDrop List, �קK���e�Q���
2: �W�[ Repeat Tray �\��
3: �b�S���إߤu�檺���p, �i�H�� Run Page ���ɮ׸�T��s�XDevice Seup �ק� Tray File
4: �b�S���إߤu�檺���p, �i�H�� Run Page ���ɮ׸�T��s�XRepeat Tray �ק�]�w
5: Run Page �W�[ Visual Panel ��K�ϥ�
6: Run Page �W�[ Tray Stat �\��, �Ψ��˵�, �ثe Repeat Tray ��/�񪺸�T
7: Run Page �W�[ Tray Color �\��, �Ψӽվ� Repeat Tray ��ܸ�T, ��UTray File���Ҧ�

V1.0Ad
1: �i�z�L�@m.Setting.m_bCancelDoubleChkChange, �p�G�����ܰѼ�, �M�w���}���n���n�V�ϥΪ̽T�{,1��ܭn�T�{
2: �W�[�Y��Ū�� Test Site Drive, Torque status(%) �\��, ���W���F�s���u, �åB�bCom Port���]�w�۹����s���f
�M��� \System\3111.System �� Enable Torque Status=1 �]�w��1, ���򭫶}�n��, Initial ������, �N�|�}�lŪ��Torque
3: �ץ�Ū�� CDriverMotorTorqueControl ���ͪ����D
4: Repeat Tray, Max Value, �b Basic Setting �אּ�i�H�]�w, �ӫD Disable
5: �ץ� Alarm Mail �Ѻc�y�����{���� Delay
6: �ץ� West �Ѻc�y�����{�����o Memory leak

V1.0Ae
1: �ץ� CWest �����������í�w�����D
2: �ץ� Repeat Tray Output Z down

V1.0Af
1: �W�[ Lamp Setup �\��, �i�ۥѳ]�w �T����ܿO���欰�Ҧ�
2: �ק� Ts Counter �אּ�i�H�� Engineer �ק�
3: �ק� Ts Counter �i�H�� Run Page ���}, �îھڤ��P���v��, �M�w�i���i�H�M��
4: �W�[ DMSG �ΨӬ����}�����L�{�O�_���T
5: �ץ� Lot Done Prograss, �אּ�n Handle Thread �O�_�Q����
6: �ק� UpdataMainMsg, �� Door Disable ���ܬ��{�{
7: �ץ� OpenCamera(int nCamID, bool bDisplayProperties, int nWidth, int nHeight),
�� Camera ����������, �{���Ұʳy�������
8: �ק�, ���� CMotor �������� MC8141PSetRange(pAxis->BoardID, 0, 8000000);
9: �ץ�, CMotor, MotorRunAway �̭����t��, �Ѹ��J�ɮ׳t�׭קאּ�T�w 10%�t��, �H�קKInitial ArmXY ���I��í�w
10: �ץ� CThIOReadWriteRemoteIO::SetTorque(), �L�k�]�w�� 10 Volt�����D
11: �ץ� Jam Rate Report �p���`�ƶq�����~
12: �ץ� CCameraDS::CloseCamera(), �S���� Detach(); , �y���Ѻc�� return code ���`
13: �ץ� InitOutputColor, �S�����J�C�⪺���D
14: �s�W Arm Log Image �\��, �B�त�C���� IC �e�n����, �C���إߤ@���s���u�泣�|�ھڤu�沣�ͤ@����Ƨ�, �Ψ��x�s�ɮ�
( �ɦW�榡 : 002_Tray1_001.jpg ( ICLocation_TrayFrom_RepeatTimes.jpg ), ��Ƨ��榡 : yyyy_mm_dd_hhss_LotNo
15: �W�[ Tray File Mode, Remote ����
16: �W�[ GDIPlus, // GDIPlus ���O, �Ψ�����
17: �ץ� LoadCounter, SaveCounter �g���}�C�����D
18: �ק� �w�]���A�ܧ� AutoSkip ���ﶵ, ���H�ɮ׬���
19: �ץ� ThIOReadWritaRemoteIO ���� ND_ReadBackDO �H�קK�}�� HeaterOn ���`
20: �ק� Lot Information �i�H��� TrayFile
21: �ק� Lot Done Progress �۰ʮ���

V1.0Ag
1: �ק� _InitialInPosRange �� 1 �קאּ 2, �קKInitial �e�� Timeout
2: �ק� MotorRunAway, �ק�U�R�O�e�����ݮɶ�, �קK pulse ���ʫe�y���~�P
3: �ק� MotorRunAway, �ק� �T�{���S���~�P

V1.0Ah
1: �ק� Manual Contact, Torque �קאּ Contact Force
2: �ק� Summary Report ���, ���D�� Summary Report List �קאּ Summary Report
3: �ק� Offset ���, Input(Place), Ouput(Pick) �קאּ Place, Pick, �קK�Ȥ�V�c
4: �ק� IO Monitor ���, Rotator �� Missing LED �קאּ Present
5: �s�W Manual Contact, �W�[�ާ@����
6: �s�W Offset, OffsetTs �W�[��컡��
7: �ק� Extend Function, �p�G Rotator �\������, �h����ܿﶵ, �p�G�Ұ�, �h��ܿﶵ, �H�קK�Ȥ�V�c
8: �ק� �U�������, �p�G�ӭ����O�ھ� TrayFile, �h�����|�Хܬ� Tray, 
�p�G�ӭ����O���H Machine �h�����|�Х� Machine, 
ex: TrayFile -> [Tray File Information], Machine -> [Machine File Information]
Handler: TrayColorDef, AutoRetry, RepeatTray, TowerSetting, Motor Monitor, Alignment, TS Counter, Alarm Mail
Tray: Site Setting, Yield Control, Offset, Speed, Timer, Catoregy, Offset TS
9: ���� Simulation Setting �����Ѽ�
10: ���� Loop Test �����Ѽ�
11: �W�[ ErrorCode: enCodeTestSiteMoveICMissing	(606 Test Site move to place, IC missing), 
�� Test Site �U���h Socket ��IC��, �h�p�G�s���ˬd��35��IO����,�h���IC����, 
�h�|�N Test Site�԰_, �M��o�XAlarm, �ШϥΪ̫��U Test Site Skip ���� ����IC��, �~��B��
12: �ק� Arm Log Image, �u���Ұʸӥ\��, �~�s�W��Ƨ�
13: �ק� Initial ���ɭ�, �p�G Shuttle �w�g���b Pick/Place����m, �h�̫�~�^�� Home
�H�קK�p�GInitial��, �̫ᰱ����m�O TestSite��Shuttle Pick IC, �|�y�� TestSite �ɨ�@�b, ��M�Q�Ԧ^ Home,�ɭPWorkpress�l�a
14: �ק� �p�G���{��, �̫ᰱ����m�O TestSite��Shuttle Pick IC, �|�y�����{���� Shuttle �|�Ԧ� Test Site �y�� Wrokpress �l��
�]�� �o�{�̫ᰱ����m�O Pick/Place��m, �h�j���]�w�� Pick/Place����m
15: �ץ� Tester Setting, Interface Setting IP ��ܿ��~�����D, �s�W GetHandlerIPAddress() ���o���TIP

V 1.0Ai
1: �ץ� Error Code, 509 �p�G�b Shuttle Pick IC ���ɭ�, �p�G Retry �|�y����^��IC ArmLog ���ȿ��~, �ɭP
��� -1 �����~��m, �w�ץ�

V 1.0Aj
1: �W�[ MoveOffnNLimit, �T�O Initial �@�w�|���T���}�t����
2: �ק� Arm Z Initial, �N MotorMovetonLimt �ܧ� MotorMovetonNLimt, �H�T�O�T�����T, ���|�]���u�ȷ����T���{�@�U,
�y���t�� Initial ���`
3: �W�[ Pass/Fail �Ҧ��bRepeat Tray, �]���ק� GetRepeatTrayModeMoation(), �W�[ ResetInputStatus()
�W�[ ErrorCode: enCodeArmOutputTray1Full (516 Tray1 Fail Full),	enCodeArmOutputTray2Full (517 Tray2 Fail Full)
4: �W�[ SLT Protocol �\��,
5: �W�[ RemoteErrorMessage, �ΨӶǰe Event �ƥ�
6: �ץ� enToOutputHomeEnd, �g�J BinLog ���~, �ɭP�L�k���T���ͳ���
7: �ץ� Initial ��ֳ�������ɪ��ɶ�
8: �s�W InitialMissionOnTheGo(), SetRemoteCoordRequest(), GetRemoteCoordRequest(), 
�q�� ThArm �}�l���� Coordnation ����

V 1.0Ak
1: �ץ� SLT Protocol �û��L�k�}�Ҧ��\�����~
2: �W�[ tagRemoteCtrlFun, �ΨӶ}�һP�]�w�����\��

V 1.0Al
1: �ק� SLT Protocol �欰�Ҧ�, �W�[ SetStateErrorCtrlDone
2: �ק� SLT Protocol ���ثe baund rate 115200 -> 9600
3: �ץ� SetSiteTemp �S������ūת����D, �åB�⭭��}�� 145.00
4: �s�W UpdateYieldSetting, �קK RunPage ���}�v���{�{

V 1.0Am
1: �s�W SLT Protocol �R�O, SetTestSiteVacc, ����ծ�, �Ψ�����, Test Site Vacc
2: �b SetErrorMessage ��, Demo �Ҧ��W�[
3: �W�[ RepeatTrayReport �\��,�bRepeat Tray�Ҧ��U, 
�p�G�]�w�� Both/Disable, Disable/Both, Both/Both �N�|���ͳ���, ���O Bin(H/W) �]���S���ھ�H/W ��Bin, �]���w�]�Ȭ� None

V 1.0An
1: �s�W CDlgTrayMapRepeat ���, �ΨӪ��Repeat Tray�Ҧ��U, �ثeTray Map���榡
# �W�[ RepeatTray, TrayMap����TrayMap�\��,SaveTrayMapRepeat, LoadTrayMapRepeat, AddTrayMapRepeat
# �W�[ LotDoneClearTrayMapRepeat, �b LotDone ��, �M�� Repeat Tray ���������
# �s�W _Output_Stack_Number, m.TrayMapRepeat, �ΨӳB�zRepeat Tray������TrayMap���
# �ק� CViewTrayMap �t�X RepeatTray �Ҧ��U��ø��
# RepeatTray TrayMap
2: �b Demo �Ҧ��U, �|�Ұ� RS232/TCP/IP

V 1.0Ao
1: �ק� �b Demo �Ҧ��U, �|���� RS232/TCP/IP
2: SLT Protocol �ק�
# �W�[ CDriverTestInterfaceTCP (m_TesterInterfaceTcp), TCP/IP �h
# �ק� Cordnation ��l��Col,Row,Tray ���w�]�ȥ�-1,�ର0
# �W�[ GetBaudRate ���o ��e BaudRate �ƭ�

3: �ק� Initial (Page Initial) �e��, ���Y����ܪ����Ԫ�, �H�קK��ƻ\�L
4: �ק� Interface Setting, TCP/IP ������, �H�קK����_��
5: �s�W User Page �� SLT Protocol Dialog, �]�ABasic Setting�Ψ���ܳ]�w, 
Monitor�ΨӧY����ܰT��, Help �Ψ���ܥثe�����O��

V 1.0Ap
1: SLT Protocol �ק�
# �W�[ InitTestInterfaceExcute, �N ProcessCommand, �W�ߥX�ӳB�z

V1.0Aq
1: SLT Protocol �ק�
# �ק� SETCOORDNATESRETURN, <<SETCOORDNATIONRETURN: DONE>> �קאּ <<SETCOORDINATESRETURN: DONE>>

V1.0Ar
1: SLT Protocol �ץ�
# �ץ� ReadTCP, �]�������� TCP, Serial ��Ƽh�y���ѽX���~

V1.0As
1: �W�[ Repeat Tray Yield Rate

V1.0At
1: �b Setup Page, TrayMapSetting, �p�G�b�Ұ�Repeat Tray�����p�U
�Ұ� TrayMapSetting, �|�ର Repeat Tray
2: 







 

