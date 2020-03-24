import random

from textmagic.rest import TextmagicRestClient
  
username = "diogocosta"

token = "uHTMS2HgLkamREoKuo3QKpEf9IgFN4"
client = TextmagicRestClient(username, token)

tokenEnviar = str(random.randint(100000, 999999))
print(tokenEnviar)
  
message = client.messages.create(phones="00351914215212", text="Hello TextMagic")