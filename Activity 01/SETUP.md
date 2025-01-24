# Windows Subsystem for Linux (WSL)

## Step 1: เปิด Windows Powershell

กดที่ปุ่ม Windows จากนั้นค้นหา `Windows Powershell` จากนั้นกดคลิกขวา แล้วคลิกที่ `Run as administrator`

[INSERT IMAGE HERE]

เมื่อเปิดเสร็จแล้วให้รันคำสั่งนี้

```
Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
```

> [!NOTE]
> เมื่อรันเสร็จแล้ว ตัว Powershell อาจจะขอให้เรา Restart เครื่อง ก็ให้ Restart เครื่องไปเลย

## Step 2: Download Ubuntu

กดที่ปุ่ม Windows จากนั้นค้นหา `Microsoft Store` จากนั้นค้นหา `Ubuntu` แล้วจะพบหน้านี้

[INSERT IMAGE HERE]

ให้เรากด `Install` แล้วพอติดตั้งโปรแกรมเสร็จสิ้น สามารถกด `Open` เพื่อใช้งาน Ubuntu ได้เลย

[INSERT IMAGE HERE]

---

# Oracle VirtualBox
