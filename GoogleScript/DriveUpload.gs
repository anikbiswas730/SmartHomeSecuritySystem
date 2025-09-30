function doPost(e) {
  try {
    var folderID = e.parameter.folder || "YOUR_FOLDER_ID";
    var folder = DriveApp.getFolderById(folderID);
    var data = Utilities.base64Decode(e.postData.contents);
    var blob = Utilities.newBlob(data, "image/jpeg", "intruder.jpg");
    folder.createFile(blob);
    return ContentService.createTextOutput("SUCCESS");
  } catch (f) {
    return ContentService.createTextOutput("ERROR: " + f.toString());
  }
}
