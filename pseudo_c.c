
int __cdecl main(int _Argc,char **_Argv,char **_Env)

{
  int iVar1;
  SHORT key_state;
  int iVar3;
  ostream *poVar4;
  longlong lVar5;
  tagINPUT *ptVar6;
  tagINPUT local_b8;
  undefined4 local_90;
  undefined4 local_7c;
  undefined4 local_68;
  undefined4 local_54;
  tagPOINT cursorPos;
  COLORREF local_30;
  COLORREF local_2c;
  HDC local_28;
  int local_20;
  int local_1c;
  
  __main();
  std::cout << "Move your mouse to the target and press Z...\n";
  while( true ) {
    key_state = GetAsyncKeyState(0x5a);
    if (key_state < 0) break;
    Sleep(1);
  }
  GetCursorPos(&cursorPos);
  local_1c = cursorPos.x;
  local_20 = cursorPos.y;
  local_28 = GetDC((HWND)0x0);
  if (local_28 == (HDC)0x0) {
    std::operator<<((longlong *)&std::cerr,"Failed to get screen device context.\n");
    return 1;
  }
  local_2c = GetPixel(local_28,local_1c,local_20);
  poVar4 = (ostream *)std::operator<<((longlong *)&std::cout,"Target position: (");
  poVar4 = std::ostream::operator<<(poVar4,local_1c);
  poVar4 = (ostream *)std::operator<<((longlong *)poVar4,", ");
  poVar4 = std::ostream::operator<<(poVar4,local_20);
  std::operator<<((longlong *)poVar4,")\n");
  poVar4 = (ostream *)std::operator<<((longlong *)&std::cout,"Target color: RGB(");
  poVar4 = std::ostream::operator<<(poVar4,local_2c & 0xff);
  poVar4 = (ostream *)std::operator<<((longlong *)poVar4,", ");
  poVar4 = std::ostream::operator<<(poVar4,local_2c >> 8 & 0xff);
  poVar4 = (ostream *)std::operator<<((longlong *)poVar4,", ");
  poVar4 = std::ostream::operator<<(poVar4,local_2c >> 0x10 & 0xff);
  std::operator<<((longlong *)poVar4,")\n");
  std::operator<<((longlong *)&std::cout,"Now watching for color match...\n");
  do {
    do {
      local_30 = GetPixel(local_28,local_1c,local_20);
    } while (local_30 != local_2c);
    ptVar6 = &local_b8;
    for (lVar5 = 0xf; lVar5 != 0; lVar5 = lVar5 + -1) {
      *(undefined8 *)ptVar6 = 0;
      ptVar6 = (tagINPUT *)&ptVar6->field1_0x8;
    }
    local_b8.type = 0;
    local_b8.field1_0x8.mi.dwFlags = 0x8001;
    iVar1 = local_1c * 0xffff;
    iVar3 = GetSystemMetrics(0);
    local_b8.field1_0x8.mi.dx = iVar1 / iVar3;
    iVar1 = local_20 * 0xffff;
    iVar3 = GetSystemMetrics(1);
    local_b8.field1_0x8.mi.dy = iVar1 / iVar3;
    local_90 = 0;
    local_7c = 2;
    local_68 = 0;
    local_54 = 4;
    SendInput(3,&local_b8,0x28);
  } while( true );
}

