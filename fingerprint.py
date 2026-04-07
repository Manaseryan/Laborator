import platform
import uuid
import shutil
import hashlib
import os
import re

cpu_model = platform.processor().strip()

mac_num = uuid.getnode()
mac_address = ':'.join(re.findall('..', '%012x' % mac_num))

disk_path = "C:\\" if os.name == 'nt' else "/"
disk_size = str(shutil.disk_usage(disk_path).total)

raw_string = f"{cpu_model}{mac_address}{disk_size}"
print(f"Raw info: {raw_string}")

fingerprint = hashlib.sha256(raw_string.encode('utf-8')).hexdigest()
print(f"System fingerprint: {fingerprint}")