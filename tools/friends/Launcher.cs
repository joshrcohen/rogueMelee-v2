// RogueMelee-v2 Friends Launcher, 1.0.0. Original implementation, MIT licensed.
// Compatible with the C# 5 compiler and .NET Framework 4.x included with Windows 10/11.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using System.Windows.Forms;

[assembly: AssemblyTitle("RogueMelee v2 Friends Launcher")]
[assembly: AssemblyDescription("Verified public-release updater and offline Dolphin launcher")]
[assembly: AssemblyVersion("1.0.0.0")]
[assembly: AssemblyFileVersion("1.0.0.0")]

namespace RogueFriends {
    public static class Constants {
        public const string Version = "1.0.0";
        public const string Repo = "joshrcohen/rogueMelee-v2";
        public const string Api = "https://api.github.com/repos/" + Repo + "/releases?per_page=100";
        public const string Releases = "https://github.com/" + Repo + "/releases";
        public const string SourceMD5 = "0e63d4223b01d9aba596259dc155a174";
        public const string SourceDolSHA1 = "08e0bf20134dfcb260699671004527b2d6bb1a45";
        public const string XdeltaZip = "https://github.com/jmacd/xdelta/releases/download/v3.2.0/xdelta3-3.2.0-windows-x86_64.zip";
        public const string XdeltaSHA256 = "af8ef036cb077a48df080c9a8ac1be4a6e7511c32d11f8bec89b6803a9e52576";
        public const long MaxPatch = 2L * 1024 * 1024 * 1024;
        public const long MaxImage = 4L * 1024 * 1024 * 1024;
        public static readonly string Data = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "RogueMelee-v2");
        public static readonly string Reports = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "RogueMelee-v2", "Crash Reports");
        public static readonly string Profile = Path.Combine(Data, "DolphinUser");
    }
    public sealed class Settings {
        public string Source = "";
        public string Output = Path.Combine(Constants.Data, "Game", "RogueMelee-v2.iso");
        public string Dolphin = "";
        public bool Testing = true;
        public bool AutoPlay = true;
        public bool AutoUpdate = true;
        public bool ControllerImportAttempted = false;
        public long PausedRelease = 0;
    }
    public sealed class Install {
        public long ReleaseId;
        public string Tag, Fingerprint, Output, OutputSHA256, PatchSHA256, GitCommit, InstalledAt;
        public long OutputBytes;
    }
    public sealed class Journal {
        public string Target, Staged, Backup;
        public Install Next, Previous;
    }
    public sealed class Asset {
        public long Id, Size;
        public string Name, Url, Digest;
    }
    public sealed class Release {
        public long Id;
        public string Tag, Name, Body;
        public bool Prerelease;
        public DateTimeOffset Published;
        public List<Asset> Assets = new List<Asset>();
    }
    public sealed class Package {
        public Release Release;
        public Asset Patch;
        public string PatchSHA256, OutputSHA256, GitCommit;
        public long OutputBytes;
        public string Fingerprint { get { return Release.Id.ToString(CultureInfo.InvariantCulture) + ":" + PatchSHA256 + ":" + OutputSHA256; } }
    }
    public sealed class ProgressInfo {
        public string Text;
        public int Percent;
        public ProgressInfo(string text, int percent) { Text = text; Percent = percent; }
    }

    public static class Util {
        public static string Hex(byte[] b) { return BitConverter.ToString(b).Replace("-", "").ToLowerInvariant(); }
        public static string GetString(IDictionary<string, object> o, string key) { object x; return o.TryGetValue(key, out x) && x != null ? Convert.ToString(x, CultureInfo.InvariantCulture) : ""; }
        public static long GetLong(IDictionary<string, object> o, string key) { object x; return o.TryGetValue(key, out x) && x != null ? Convert.ToInt64(x, CultureInfo.InvariantCulture) : 0; }
        public static bool GetBool(IDictionary<string, object> o, string key) { object x; return o.TryGetValue(key, out x) && x != null && Convert.ToBoolean(x, CultureInfo.InvariantCulture); }
        public static bool IsHash(string value, int length) { return value != null && Regex.IsMatch(value, "\\A[0-9a-fA-F]{" + length + "}\\z"); }
        public static string RequireHash(string value, int length, string label) { if (!IsHash(value, length)) throw new InvalidDataException("The release has a missing or invalid " + label + ". Ask Josh to republish the patch and build-manifest.json together."); return value.ToLowerInvariant(); }
        public static string Quote(string arg) {
            // CommandLineToArgvW/MS C runtime quoting; never pass these arguments through cmd.exe.
            StringBuilder b = new StringBuilder("\""); int slashes = 0;
            foreach (char c in arg) { if (c == '\\') { slashes++; continue; } if (c == '"') { b.Append('\\', slashes * 2 + 1); b.Append('"'); slashes = 0; continue; } b.Append('\\', slashes); slashes = 0; b.Append(c); }
            b.Append('\\', slashes * 2); b.Append('"'); return b.ToString();
        }
        public static bool SamePath(string a, string b) { return !String.IsNullOrWhiteSpace(a) && !String.IsNullOrWhiteSpace(b) && String.Equals(Path.GetFullPath(a).TrimEnd('\\', '/'), Path.GetFullPath(b).TrimEnd('\\', '/'), StringComparison.OrdinalIgnoreCase); }
        public static void DeleteFile(string path) { try { if (File.Exists(path)) File.Delete(path); } catch { } }
        public static void AtomicText(string path, string text) {
            Directory.CreateDirectory(Path.GetDirectoryName(path)); string temp = path + ".tmp-" + Guid.NewGuid().ToString("N");
            try { File.WriteAllText(temp, text, new UTF8Encoding(false)); using (FileStream s = new FileStream(temp, FileMode.Open, FileAccess.ReadWrite, FileShare.None)) s.Flush(true); if (File.Exists(path)) File.Replace(temp, path, null); else File.Move(temp, path); }
            finally { DeleteFile(temp); }
        }
        public static void SaveJson(string path, object obj) { AtomicText(path, new JavaScriptSerializer().Serialize(obj)); }
        public static T LoadJson<T>(string path) { return new JavaScriptSerializer { MaxJsonLength = 2 * 1024 * 1024 }.Deserialize<T>(File.ReadAllText(path)); }
        public static string HashFile(string path, string algorithm, CancellationToken cancel, Action<ProgressInfo> progress, string label) {
            using (HashAlgorithm hash = algorithm == "MD5" ? (HashAlgorithm)MD5.Create() : algorithm == "SHA1" ? (HashAlgorithm)SHA1.Create() : SHA256.Create())
            using (FileStream file = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read, 1024 * 1024, FileOptions.SequentialScan)) {
                byte[] buf = new byte[1024 * 1024]; long done = 0; int n; long last = 0;
                while ((n = file.Read(buf, 0, buf.Length)) > 0) { cancel.ThrowIfCancellationRequested(); hash.TransformBlock(buf, 0, n, buf, 0); done += n; if (Environment.TickCount - last >= 100 || done == file.Length) { last = Environment.TickCount; if (progress != null) progress(new ProgressInfo(label, file.Length == 0 ? 100 : (int)(done * 100 / file.Length))); } }
                hash.TransformFinalBlock(new byte[0], 0, 0); return Hex(hash.Hash);
            }
        }
        public static byte[] ReadExact(Stream s, int count) { byte[] b = new byte[count]; int n = 0, r; while (n < count) { r = s.Read(b, n, count - n); if (r == 0) throw new EndOfStreamException("The image is incomplete."); n += r; } return b; }
        public static uint BE(byte[] b, int at) { return ((uint)b[at] << 24) | ((uint)b[at + 1] << 16) | ((uint)b[at + 2] << 8) | b[at + 3]; }
        public static void VerifySource(string path, CancellationToken token, Action<ProgressInfo> progress) {
            if (!File.Exists(path)) throw new FileNotFoundException("Select your ORIGINAL clean Melee NTSC-U 1.02 ISO. Keep it for all future updates.");
            if (HashFile(path, "MD5", token, progress, "Checking your clean Melee ISO (read-only)...") != Constants.SourceMD5)
                throw new InvalidDataException("This is not the expected clean Melee NTSC-U 1.02 ISO. Do not select the old RogueMelee ISO or another mod.\r\n\r\nExpected MD5: " + Constants.SourceMD5 + "\r\nYour original file has NOT been modified.");
            using (FileStream s = File.OpenRead(path)) {
                byte[] h = ReadExact(s, 0x440); if (Encoding.ASCII.GetString(h, 0, 6) != "GALE01") throw new InvalidDataException("Unexpected source game ID.");
                long start = BE(h, 0x420); if (start < 0x2440 || start + 256 > s.Length) throw new InvalidDataException("Invalid source DOL offset.");
                s.Position = start; byte[] dol = ReadExact(s, 256); long length = 256;
                for (int i = 0; i < 18; i++) { long size = BE(dol, 0x90 + i * 4); if (size == 0) continue; long offset = BE(dol, i * 4); if (offset < 256 || offset + size > 32 * 1024 * 1024) throw new InvalidDataException("Invalid source DOL layout."); length = Math.Max(length, offset + size); }
                if (start + length > s.Length) throw new InvalidDataException("Truncated source DOL."); s.Position = start;
                using (SHA1 sha = SHA1.Create()) { if (Hex(sha.ComputeHash(ReadExact(s, (int)length))) != Constants.SourceDolSHA1) throw new InvalidDataException("The source DOL does not match unmodified Melee 1.02."); }
            }
        }
        public static void RequireDisk(string output, long bytes) {
            string root = Path.GetPathRoot(Path.GetFullPath(output)); if (!root.StartsWith("\\\\", StringComparison.Ordinal)) { DriveInfo drive = new DriveInfo(root); if (drive.IsReady && drive.AvailableFreeSpace < bytes) throw new IOException("Not enough free disk space on " + root + ". Free at least " + Math.Ceiling(bytes / 1073741824.0).ToString("0") + " GB before retrying. The current game was not replaced."); }
        }
        public static string Tail(string path, int bytes) {
            try { using (FileStream s = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite | FileShare.Delete)) { s.Position = Math.Max(0, s.Length - bytes); return Encoding.UTF8.GetString(ReadExact(s, (int)(s.Length - s.Position))); } } catch { return "[Log not available]"; }
        }
        public static string Redact(string text) { string p = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile); return String.IsNullOrEmpty(p) ? text : Regex.Replace(text, Regex.Escape(p), "%USERPROFILE%", RegexOptions.IgnoreCase); }
    }

    public sealed class Store {
        public string ConfigPath { get { return Path.Combine(Constants.Data, "settings.json"); } }
        public string InstalledPath { get { return Path.Combine(Constants.Data, "installed.json"); } }
        public string PreviousPath { get { return Path.Combine(Constants.Data, "previous.json"); } }
        public string JournalPath { get { return Path.Combine(Constants.Data, "pending-install.json"); } }
        public Settings Config;
        public Install Current;
        public Store() {
            Directory.CreateDirectory(Constants.Data); Directory.CreateDirectory(Constants.Reports);
            Config = File.Exists(ConfigPath) ? Util.LoadJson<Settings>(ConfigPath) : new Settings();
            if (Config == null) throw new InvalidDataException("settings.json is empty. Move it aside and restart the launcher.");
            Current = File.Exists(InstalledPath) ? Util.LoadJson<Install>(InstalledPath) : null;
            if (String.IsNullOrEmpty(Config.Dolphin)) {
                string old = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "RogueMelee", "launcher.cfg");
                try { string[] lines = File.ReadAllLines(old); string path = Encoding.UTF8.GetString(Convert.FromBase64String(lines[1])); if (File.Exists(path)) Config.Dolphin = path; } catch { }
            }
        }
        public void Save() { Util.SaveJson(ConfigPath, Config); }
        public void Recover(CancellationToken token, Action<ProgressInfo> progress) {
            if (!File.Exists(JournalPath)) return;
            Journal j = Util.LoadJson<Journal>(JournalPath);
            if (j == null || j.Next == null || !Util.IsHash(j.Next.OutputSHA256, 64) || !Util.SamePath(j.Target, j.Next.Output) || !Util.SamePath(j.Backup, j.Target + ".previous")) throw new InvalidDataException("An invalid interrupted-install record exists. Your files were left untouched; open the launcher log for its path.");
            if (File.Exists(j.Target) && Util.HashFile(j.Target, "SHA256", token, progress, "Recovering interrupted update...") == j.Next.OutputSHA256) {
                Util.SaveJson(InstalledPath, j.Next); Current = j.Next; if (j.Previous != null) Util.SaveJson(PreviousPath, j.Previous); Util.DeleteFile(j.Staged); Util.DeleteFile(JournalPath); return;
            }
            if (!File.Exists(j.Target) && File.Exists(j.Backup) && j.Previous != null) {
                if (Util.HashFile(j.Backup, "SHA256", token, progress, "Checking recovery copy...") != j.Previous.OutputSHA256) throw new InvalidDataException("Recovery copy failed its checksum; no files were overwritten.");
                File.Move(j.Backup, j.Target);
            }
            if (j.Previous != null && File.Exists(j.Target) && Util.HashFile(j.Target, "SHA256", token, progress, "Verifying previous game...") == j.Previous.OutputSHA256) { Util.SaveJson(InstalledPath, j.Previous); Current = j.Previous; }
            else if (File.Exists(j.Target)) throw new InvalidDataException("An interrupted update needs manual inspection. The existing ISO has been preserved.");
            Util.DeleteFile(j.Staged); Util.DeleteFile(JournalPath);
        }
        public bool HasInstall { get { return Current != null && File.Exists(Current.Output); } }
        public void Commit(string staged, Install next) {
            string target = next.Output, backup = target + ".previous";
            Install prev = Current != null && Util.SamePath(Current.Output, target) ? Current : null;
            if (File.Exists(target) && prev == null) throw new IOException("An unrelated file already exists at the output path. Choose a different game location; it will not be overwritten.");
            Util.SaveJson(JournalPath, new Journal { Target = target, Staged = staged, Backup = backup, Next = next, Previous = prev });
            if (prev != null) Util.SaveJson(PreviousPath, prev); else Util.DeleteFile(PreviousPath);
            if (File.Exists(target)) { Util.DeleteFile(backup); File.Replace(staged, target, backup, true); }
            else File.Move(staged, target);
            Current = next; Util.SaveJson(InstalledPath, next); Config.Output = target; Save(); Util.DeleteFile(JournalPath);
        }
    }

    public static class Network {
        public static void ValidateUrl(string address, bool releaseAsset) {
            Uri uri; if (!Uri.TryCreate(address, UriKind.Absolute, out uri) || uri.Scheme != "https" || !String.IsNullOrEmpty(uri.UserInfo) || !uri.IsDefaultPort) throw new InvalidDataException("Only trusted HTTPS download URLs are allowed.");
            string host = uri.Host.ToLowerInvariant();
            string[] hosts = { "github.com", "api.github.com", "release-assets.githubusercontent.com", "objects.githubusercontent.com", "github-releases.githubusercontent.com" };
            if (!hosts.Contains(host)) throw new InvalidDataException("Untrusted download host: " + host);
            if (releaseAsset && (host != "github.com" || !uri.AbsolutePath.StartsWith("/" + Constants.Repo + "/releases/download/", StringComparison.OrdinalIgnoreCase))) throw new InvalidDataException("The asset URL is not a release download from " + Constants.Repo + ".");
        }
        static HttpWebResponse Open(string url, CancellationToken token) {
            for (int hop = 0; hop < 6; hop++) {
                token.ThrowIfCancellationRequested(); ValidateUrl(url, false);
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(url); req.UserAgent = "RogueMelee-v2-Friends/" + Constants.Version; req.AllowAutoRedirect = false;
                req.Timeout = 30000; req.ReadWriteTimeout = 60000; req.AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate;
                if (new Uri(url).Host == "api.github.com") { req.Accept = "application/vnd.github+json"; req.Headers["X-GitHub-Api-Version"] = "2022-11-28"; }
                HttpWebResponse response;
                try { using (token.Register(delegate { req.Abort(); })) response = (HttpWebResponse)req.GetResponse(); }
                catch (WebException e) {
                    token.ThrowIfCancellationRequested(); HttpWebResponse r = e.Response as HttpWebResponse;
                    if (r != null) { int code = (int)r.StatusCode; string limit = r.Headers["X-RateLimit-Remaining"]; r.Close();
                        if (code == 404) throw new IOException("GitHub cannot find the repository or release asset. It must be public, and the release must be published (not a draft).", e);
                        if (code == 403 || code == 429) throw new IOException(limit == "0" ? "GitHub's public request limit was reached. Wait before checking again; Play installed still works offline." : "GitHub temporarily refused the download. Try again later; Play installed still works offline.", e);
                    }
                    throw new IOException("Cannot reach GitHub. Check your connection or choose Play installed. " + e.Message, e);
                }
                int status = (int)response.StatusCode;
                if (status >= 300 && status <= 399) { string location = response.Headers["Location"]; response.Close(); if (String.IsNullOrEmpty(location)) throw new IOException("GitHub returned an empty redirect."); url = new Uri(new Uri(url), location).AbsoluteUri; continue; }
                return response;
            }
            throw new IOException("Too many download redirects.");
        }
        public static string Text(string url, int maxBytes, CancellationToken token) {
            using (HttpWebResponse r = Open(url, token)) using (Stream input = r.GetResponseStream()) using (MemoryStream output = new MemoryStream()) {
                byte[] buf = new byte[32768]; int n; while ((n = input.Read(buf, 0, buf.Length)) > 0) { token.ThrowIfCancellationRequested(); if (output.Length + n > maxBytes) throw new InvalidDataException("GitHub response exceeded the size limit."); output.Write(buf, 0, n); }
                return Encoding.UTF8.GetString(output.ToArray()).TrimStart('\uFEFF');
            }
        }
        public static void Download(string url, string path, long expectedSize, long limit, CancellationToken token, Action<ProgressInfo> progress, string label) {
            string tmp = path + ".partial-" + Guid.NewGuid().ToString("N"); Directory.CreateDirectory(Path.GetDirectoryName(path));
            try {
                using (HttpWebResponse r = Open(url, token)) using (Stream input = r.GetResponseStream()) using (FileStream output = new FileStream(tmp, FileMode.CreateNew, FileAccess.Write, FileShare.None)) {
                    if (r.ContentLength > limit) throw new InvalidDataException("Download exceeds the allowed size."); long total = expectedSize > 0 ? expectedSize : r.ContentLength;
                    byte[] buf = new byte[262144]; int n; long done = 0, last = 0;
                    while ((n = input.Read(buf, 0, buf.Length)) > 0) { token.ThrowIfCancellationRequested(); done += n; if (done > limit || (expectedSize > 0 && done > expectedSize)) throw new InvalidDataException("The download size does not match the release."); output.Write(buf, 0, n); if (Environment.TickCount - last > 100 || done == total) { last = Environment.TickCount; progress(new ProgressInfo(label + "  " + (done / 1048576.0).ToString("0.0") + " MB", total > 0 ? (int)Math.Min(100, done * 100 / total) : -1)); } }
                    if (done == 0 || (expectedSize > 0 && done != expectedSize)) throw new InvalidDataException("Download was incomplete. Please retry."); output.Flush(true);
                }
                Util.DeleteFile(path); File.Move(tmp, path);
            } finally { Util.DeleteFile(tmp); }
        }
        public static List<Release> ParseReleases(string json, bool includeTesting) {
            JavaScriptSerializer js = new JavaScriptSerializer { MaxJsonLength = 4 * 1024 * 1024 }; object[] rows = js.DeserializeObject(json) as object[];
            if (rows == null) throw new InvalidDataException("GitHub returned an invalid release list."); List<Release> releases = new List<Release>();
            foreach (object obj in rows) {
                IDictionary<string, object> row = obj as IDictionary<string, object>; if (row == null || Util.GetBool(row, "draft") || (!includeTesting && Util.GetBool(row, "prerelease"))) continue;
                string date = Util.GetString(row, "published_at"); DateTimeOffset published; if (!DateTimeOffset.TryParse(date, CultureInfo.InvariantCulture, DateTimeStyles.AssumeUniversal, out published)) continue;
                Release r = new Release { Id = Util.GetLong(row, "id"), Tag = Util.GetString(row, "tag_name"), Name = Util.GetString(row, "name"), Body = Util.GetString(row, "body"), Prerelease = Util.GetBool(row, "prerelease"), Published = published };
                if (r.Id <= 0 || r.Tag.Length == 0 || r.Tag.Length > 200) continue; object list; if (row.TryGetValue("assets", out list) && list is object[]) foreach (object a in (object[])list) {
                    IDictionary<string, object> x = a as IDictionary<string, object>; if (x == null || Util.GetString(x, "state") != "uploaded") continue;
                    r.Assets.Add(new Asset { Id = Util.GetLong(x, "id"), Size = Util.GetLong(x, "size"), Name = Util.GetString(x, "name"), Url = Util.GetString(x, "browser_download_url"), Digest = Util.GetString(x, "digest") });
                }
                releases.Add(r);
            }
            return releases.OrderByDescending(x => x.Published).ThenByDescending(x => x.Id).ToList();
        }
        public static Package ParsePackage(Release release, string json) {
            IDictionary<string, object> m = new JavaScriptSerializer { MaxJsonLength = 2 * 1024 * 1024 }.DeserializeObject(json) as IDictionary<string, object>;
            if (m == null) throw new InvalidDataException("Invalid build-manifest.json.");
            long schema = Util.GetLong(m, "launcher_schema"); if (schema > 1) throw new InvalidDataException("This release needs a newer launcher. Get the launcher from the Releases page.");
            string patchName = Util.GetString(m, "patch_file"); List<Asset> patches = release.Assets.Where(a => a.Name.EndsWith(".xdelta", StringComparison.OrdinalIgnoreCase)).ToList();
            if (patchName.Length > 0) patches = patches.Where(a => String.Equals(a.Name, patchName, StringComparison.Ordinal)).ToList();
            if (patches.Count != 1) throw new InvalidDataException("The release must include one .xdelta patch, or a matching patch_file in build-manifest.json. Josh needs to finish publishing this release.");
            Asset patch = patches[0]; ValidateUrl(patch.Url, true); if (patch.Size <= 0 || patch.Size > Constants.MaxPatch) throw new InvalidDataException("Invalid patch size.");
            string input = Util.GetString(m, "source_md5"); if (input.Length > 0 && !String.Equals(input, Constants.SourceMD5, StringComparison.OrdinalIgnoreCase)) throw new InvalidDataException("This release targets a different source image and is not supported by this launcher.");
            string dol = Util.GetString(m, "source_dol_sha1"); if (dol.Length > 0 && !String.Equals(dol, Constants.SourceDolSHA1, StringComparison.OrdinalIgnoreCase)) throw new InvalidDataException("Unexpected original DOL checksum in release.");
            Package package = new Package { Release = release, Patch = patch, PatchSHA256 = Util.RequireHash(Util.GetString(m, "patch_sha256"), 64, "patch SHA256"), OutputSHA256 = Util.RequireHash(Util.GetString(m, "output_sha256"), 64, "output SHA256"), GitCommit = Util.GetString(m, "git_commit"), OutputBytes = Util.GetLong(m, "output_bytes") };
            if (package.OutputBytes < 0 || package.OutputBytes > Constants.MaxImage) throw new InvalidDataException("Invalid output size in release manifest.");
            if (patch.Digest != null && patch.Digest.StartsWith("sha256:", StringComparison.OrdinalIgnoreCase) && !String.Equals(patch.Digest.Substring(7), package.PatchSHA256, StringComparison.OrdinalIgnoreCase)) throw new InvalidDataException("GitHub's patch digest disagrees with build-manifest.json. Nothing was installed.");
            return package;
        }
        public static Package Latest(bool testing, CancellationToken token, Action<ProgressInfo> progress) {
            progress(new ProgressInfo("Checking published " + (testing ? "testing and stable" : "stable") + " releases...", -1));
            List<Release> releases = ParseReleases(Text(Constants.Api, 4 * 1024 * 1024, token), testing);
            if (releases.Count == 0) return null; Release release = releases[0]; List<Asset> manifests = release.Assets.Where(a => a.Name == "build-manifest.json").ToList();
            if (manifests.Count != 1) throw new InvalidDataException("Newest published release " + release.Tag + " is missing build-manifest.json. No older release was silently substituted. Ask Josh to publish the patch and manifest together.");
            Asset manifest = manifests[0]; ValidateUrl(manifest.Url, true); if (manifest.Size <= 0 || manifest.Size > 2 * 1024 * 1024) throw new InvalidDataException("Invalid manifest size.");
            string body = Text(manifest.Url, 2 * 1024 * 1024, token); return ParsePackage(release, body);
        }
    }

    public static class Engine {
        public static string Xdelta(CancellationToken token, Action<ProgressInfo> progress) {
            string dir = Path.Combine(Constants.Data, "Tools", "xdelta-3.2.0"); Directory.CreateDirectory(dir); string zip = Path.Combine(dir, "xdelta.zip"), exe = Path.Combine(dir, "xdelta3.exe");
            if (!File.Exists(zip) || Util.HashFile(zip, "SHA256", token, null, "") != Constants.XdeltaSHA256) {
                progress(new ProgressInfo("Getting the verified xdelta patch engine (first use only)...", -1));
                Network.Download(Constants.XdeltaZip, zip, 0, 20 * 1024 * 1024, token, progress, "Downloading xdelta 3.2.0");
                if (Util.HashFile(zip, "SHA256", token, null, "") != Constants.XdeltaSHA256) { Util.DeleteFile(zip); throw new InvalidDataException("The patch engine failed its pinned SHA256 check. It will NOT be executed."); }
            }
            // Extract only the executable, to our chosen path. Never trust an archive's paths.
            using (ZipArchive archive = ZipFile.OpenRead(zip)) {
                List<ZipArchiveEntry> entries = archive.Entries.Where(e => e.Name.StartsWith("xdelta", StringComparison.OrdinalIgnoreCase) && e.Name.EndsWith(".exe", StringComparison.OrdinalIgnoreCase)).ToList();
                if (entries.Count != 1 || entries[0].Length < 1024 || entries[0].Length > 20 * 1024 * 1024) throw new InvalidDataException("Unexpected xdelta archive contents.");
                string tmp = exe + ".new"; Util.DeleteFile(tmp); using (Stream input = entries[0].Open()) using (FileStream output = new FileStream(tmp, FileMode.CreateNew, FileAccess.Write)) { input.CopyTo(output); output.Flush(true); }
                Util.DeleteFile(exe); File.Move(tmp, exe);
            }
            Util.AtomicText(Path.Combine(dir, "NOTICE.txt"), "xdelta 3.2.0 by Joshua MacDonald and contributors. Apache-2.0.\r\nSource and license: https://github.com/jmacd/xdelta/tree/v3.2.0\r\nDownloaded from the upstream release, not from the game repository.\r\n");
            return exe;
        }
        public static void RunTool(string exe, string[] args, CancellationToken token, Action<ProgressInfo> progress, string label) {
            StringBuilder errors = new StringBuilder(); object gate = new object();
            ProcessStartInfo start = new ProcessStartInfo(exe, String.Join(" ", args.Select(Util.Quote).ToArray())); start.UseShellExecute = false; start.CreateNoWindow = true; start.RedirectStandardError = true; start.RedirectStandardOutput = true; start.WorkingDirectory = Path.GetDirectoryName(exe);
            using (Process p = new Process { StartInfo = start }) {
                DataReceivedEventHandler receive = delegate(object sender, DataReceivedEventArgs e) { if (e.Data != null) lock (gate) { if (errors.Length < 65536) errors.AppendLine(e.Data); } };
                p.ErrorDataReceived += receive; p.OutputDataReceived += receive; p.Start(); p.BeginErrorReadLine(); p.BeginOutputReadLine(); Stopwatch watch = Stopwatch.StartNew();
                try { while (!p.WaitForExit(250)) { token.ThrowIfCancellationRequested(); progress(new ProgressInfo(label + "  (" + (int)watch.Elapsed.TotalSeconds + " s)", -1)); if (watch.Elapsed.TotalMinutes > 30) throw new TimeoutException("The patch/conversion operation exceeded 30 minutes. Existing files were preserved."); } p.WaitForExit(); token.ThrowIfCancellationRequested(); if (p.ExitCode != 0) { string text; lock (gate) text = errors.ToString(); throw new IOException("The patch/conversion tool failed (exit " + p.ExitCode + ").\r\n" + text); } }
                catch { try { if (!p.HasExited) { p.Kill(); p.WaitForExit(10000); } } catch { } throw; }
            }
        }
        public static string GetSource(Settings cfg, CancellationToken token, Action<ProgressInfo> progress) {
            if (!File.Exists(cfg.Source)) throw new FileNotFoundException("Your clean source image is missing. Choose it again in Settings.");
            string ext = Path.GetExtension(cfg.Source).ToLowerInvariant(); string source = cfg.Source;
            if (ext == ".rvz") {
                string tool = String.IsNullOrEmpty(cfg.Dolphin) ? "" : Path.Combine(Path.GetDirectoryName(cfg.Dolphin), "DolphinTool.exe");
                if (!File.Exists(tool)) throw new IOException("RVZ conversion needs DolphinTool.exe beside your selected Dolphin.exe. Select a current Dolphin installation, or select a clean .iso instead.");
                string folder = Path.Combine(Constants.Data, "Source"); Directory.CreateDirectory(folder); source = Path.Combine(folder, "clean-melee-1.02.iso");
                if (!File.Exists(source)) {
                    Util.RequireDisk(source, 2L * 1024 * 1024 * 1024); string tmp = source + ".partial.iso"; Util.DeleteFile(tmp);
                    try { RunTool(tool, new[] { "convert", "-i", cfg.Source, "-o", tmp, "-f", "iso" }, token, progress, "Converting your RVZ to a private clean-ISO cache..."); Util.VerifySource(tmp, token, progress); File.Move(tmp, source); } finally { Util.DeleteFile(tmp); }
                }
            }
            Util.VerifySource(source, token, progress); return source;
        }
        public static Install Apply(Store store, Package package, CancellationToken token, Action<ProgressInfo> progress, bool repairing) {
            string target = Path.GetFullPath(store.Config.Output); Directory.CreateDirectory(Path.GetDirectoryName(target));
            if (File.Exists(target) && (!store.HasInstall || !Util.SamePath(store.Current.Output, target))) throw new IOException("The output file is not an installation owned by this launcher. Choose another output filename; existing ISOs are never overwritten blindly.");
            if (Util.SamePath(target, store.Config.Source)) throw new InvalidDataException("The mod output must not be your clean source image.");
            if (!repairing && store.HasInstall && Util.SamePath(store.Current.Output, target)) VerifyInstall(store.Current, token, progress);
            string source = GetSource(store.Config, token, progress); if (Util.SamePath(target, source)) throw new InvalidDataException("The output would overwrite your clean ISO cache.");
            long imageSize = package.OutputBytes > 0 ? package.OutputBytes : new FileInfo(source).Length;
            Util.RequireDisk(target, imageSize + 256L * 1024 * 1024); Util.RequireDisk(Constants.Data, package.Patch.Size + 64L * 1024 * 1024);
            string cached = Path.Combine(Constants.Data, "Cache", package.PatchSHA256 + ".xdelta");
            if (!File.Exists(cached) || new FileInfo(cached).Length != package.Patch.Size || Util.HashFile(cached, "SHA256", token, progress, "Checking cached patch...") != package.PatchSHA256) {
                Network.Download(package.Patch.Url, cached, package.Patch.Size, Constants.MaxPatch, token, progress, "Downloading " + package.Release.Tag);
            }
            if (Util.HashFile(cached, "SHA256", token, progress, "Verifying the downloaded patch...") != package.PatchSHA256) { Util.DeleteFile(cached); throw new InvalidDataException("Patch SHA256 mismatch. Nothing was installed; retry the download."); }
            string engine = Xdelta(token, progress); string staged = target + ".install-" + Guid.NewGuid().ToString("N") + ".iso";
            try {
                RunTool(engine, new[] { "-d", "-s", source, cached, staged }, token, progress, "Building the new game; your original ISO stays unchanged...");
                FileInfo output = new FileInfo(staged); if (!output.Exists || output.Length < 0x440 || output.Length > Constants.MaxImage || (package.OutputBytes > 0 && output.Length != package.OutputBytes)) throw new InvalidDataException("The reconstructed image has an unexpected size.");
                if (Util.HashFile(staged, "SHA256", token, progress, "Verifying the finished game before installation...") != package.OutputSHA256) throw new InvalidDataException("The reconstructed ISO failed its SHA256 check. Your previous installation was preserved.");
                token.ThrowIfCancellationRequested();
                // Promotion is intentionally non-cancellable and atomic on supported NTFS volumes.
                progress(new ProgressInfo("Installing verified game and preserving the previous build...", -1));
                Install record = new Install { ReleaseId = package.Release.Id, Tag = package.Release.Tag, Fingerprint = package.Fingerprint, Output = target, OutputSHA256 = package.OutputSHA256, PatchSHA256 = package.PatchSHA256, GitCommit = package.GitCommit, OutputBytes = output.Length, InstalledAt = DateTimeOffset.UtcNow.ToString("O") };
                store.Commit(staged, record);
                try {
                    string prevHash = File.Exists(store.PreviousPath) ? Util.LoadJson<Install>(store.PreviousPath).PatchSHA256 : "";
                    foreach (string file in Directory.GetFiles(Path.Combine(Constants.Data, "Cache"), "*.xdelta")) { string hash = Path.GetFileNameWithoutExtension(file); if (Util.IsHash(hash, 64) && hash != record.PatchSHA256 && hash != prevHash) Util.DeleteFile(file); }
                } catch { /* Cache cleanup must not invalidate a successful installation. */ }
                return record;
            } finally { if (!File.Exists(store.JournalPath)) Util.DeleteFile(staged); }
        }
        public static void VerifyInstall(Install record, CancellationToken token, Action<ProgressInfo> progress) {
            if (record == null || !File.Exists(record.Output)) throw new FileNotFoundException("No installed game is available yet.");
            if (!Util.IsHash(record.OutputSHA256, 64) || new FileInfo(record.Output).Length != record.OutputBytes || Util.HashFile(record.Output, "SHA256", token, progress, "Checking the installed game...") != record.OutputSHA256) throw new InvalidDataException("The installed ISO was changed or damaged. Do not launch it. Use Repair installation from Settings.");
        }
        public static void Rollback(Store store, CancellationToken token, Action<ProgressInfo> progress) {
            if (!store.HasInstall || !File.Exists(store.PreviousPath)) throw new IOException("There is no previous build to restore.");
            Install previous = Util.LoadJson<Install>(store.PreviousPath); string backup = store.Current.Output + ".previous";
            if (previous == null || !Util.SamePath(previous.Output, store.Current.Output) || !File.Exists(backup) || Util.HashFile(backup, "SHA256", token, progress, "Verifying rollback build...") != previous.OutputSHA256) throw new IOException("The previous build is missing or failed verification. No files were changed.");
            string staged = store.Current.Output + ".rollback-" + Guid.NewGuid().ToString("N") + ".iso"; long paused = store.Current.ReleaseId;
            try { Util.RequireDisk(staged, previous.OutputBytes + 64L * 1024 * 1024); File.Copy(backup, staged); token.ThrowIfCancellationRequested(); store.Commit(staged, previous); store.Config.PausedRelease = paused; store.Save(); }
            finally { if (!File.Exists(store.JournalPath)) Util.DeleteFile(staged); }
        }
    }

    public static class Emulator {
        public static bool ValidExecutable(string path) { return File.Exists(path) && Path.GetFileName(path).EndsWith("Dolphin.exe", StringComparison.OrdinalIgnoreCase) && Directory.Exists(Path.Combine(Path.GetDirectoryName(path), "Sys")); }
        static Dictionary<string, Dictionary<string, string>> ReadIni(string file) {
            Dictionary<string, Dictionary<string, string>> data = new Dictionary<string, Dictionary<string, string>>(StringComparer.OrdinalIgnoreCase); string section = "";
            if (!File.Exists(file)) return data;
            foreach (string raw in File.ReadAllLines(file)) { string line = raw.Trim(); if (line.StartsWith("[", StringComparison.Ordinal) && line.EndsWith("]", StringComparison.Ordinal)) { section = line.Substring(1, line.Length - 2); if (!data.ContainsKey(section)) data[section] = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase); } else { int eq = line.IndexOf('='); if (eq > 0 && section.Length > 0 && !line.StartsWith("#") && !line.StartsWith(";")) data[section][line.Substring(0, eq).Trim()] = line.Substring(eq + 1).Trim(); } }
            return data;
        }
        static void Set(Dictionary<string, Dictionary<string, string>> ini, string section, string key, string value) { if (!ini.ContainsKey(section)) ini[section] = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase); ini[section][key] = value; }
        static void WriteIni(string file, Dictionary<string, Dictionary<string, string>> ini) { StringBuilder b = new StringBuilder(); foreach (KeyValuePair<string, Dictionary<string, string>> group in ini) { b.AppendLine("[" + group.Key + "]"); foreach (KeyValuePair<string, string> pair in group.Value) b.AppendLine(pair.Key + " = " + pair.Value); b.AppendLine(); } Util.AtomicText(file, b.ToString()); }
        public static void Prepare(Store store) {
            Settings cfg = store.Config; if (!ValidExecutable(cfg.Dolphin)) throw new IOException("Select the actual Dolphin.exe or Slippi Dolphin.exe next to its Sys folder, not Slippi Launcher.exe. The emulator is not bundled.");
            string target = Path.Combine(Constants.Profile, "Config"); Directory.CreateDirectory(target);
            string dolphinIni = Path.Combine(target, "Dolphin.ini"); Dictionary<string, Dictionary<string, string>> ini = ReadIni(dolphinIni);
            if (!cfg.ControllerImportAttempted) {
                List<string> candidates = new List<string>(); string dir = Path.GetDirectoryName(cfg.Dolphin); candidates.Add(Path.Combine(dir, "User")); DirectoryInfo parent = Directory.GetParent(dir); if (parent != null) candidates.Add(Path.Combine(parent.FullName, "User"));
                candidates.Add(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Dolphin Emulator")); candidates.Add(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "Dolphin Emulator")); candidates.Add(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Dolphin Emulator"));
                foreach (string root in candidates.Distinct(StringComparer.OrdinalIgnoreCase)) {
                    string config = Path.Combine(root, "Config"); if (!File.Exists(Path.Combine(config, "GCPadNew.ini")) && !File.Exists(Path.Combine(config, "Dolphin.ini"))) continue;
                    foreach (string name in new[] { "GCPadNew.ini", "WiimoteNew.ini", "Hotkeys.ini" }) { string src = Path.Combine(config, name), dst = Path.Combine(target, name); if (File.Exists(src) && !File.Exists(dst)) File.Copy(src, dst); }
                    string profiles = Path.Combine(config, "Profiles"); if (Directory.Exists(profiles)) foreach (string file in Directory.GetFiles(profiles, "*.ini", SearchOption.AllDirectories)) { string relative = file.Substring(profiles.Length).TrimStart('\\', '/'); string dest = Path.Combine(target, "Profiles", relative); Directory.CreateDirectory(Path.GetDirectoryName(dest)); if (!File.Exists(dest)) File.Copy(file, dest); }
                    Dictionary<string, Dictionary<string, string>> original = ReadIni(Path.Combine(config, "Dolphin.ini")); Dictionary<string, string> core;
                    if (original.TryGetValue("Core", out core)) for (int i = 0; i < 4; i++) { string key = "SIDevice" + i; if (core.ContainsKey(key)) Set(ini, "Core", key, core[key]); }
                    break;
                }
                cfg.ControllerImportAttempted = true; store.Save();
            }
            // Same launch constraints as v2/tools/lib/emulator.py, applied only to OUR profile.
            Set(ini, "Interface", "ConfirmStop", "False"); Set(ini, "Display", "RenderToMain", "True"); Set(ini, "Core", "EnableCheats", "False"); Set(ini, "Core", "EmulationSpeed", "1"); WriteIni(dolphinIni, ini);
            Util.AtomicText(Path.Combine(target, "Logger.ini"), "[Options]\r\nWriteToFile = True\r\nVerbosity = 3\r\n[Logs]\r\nOSREPORT = True\r\n");
        }
        public static Process Start(Store store, bool configureOnly) {
            Prepare(store); List<string> args = new List<string> { "-u", Constants.Profile };
            if (!configureOnly) { args.Add("-b"); args.Add("-e"); args.Add(store.Current.Output); }
            return Process.Start(new ProcessStartInfo(store.Config.Dolphin, String.Join(" ", args.Select(Util.Quote).ToArray())) { UseShellExecute = false, WorkingDirectory = Path.GetDirectoryName(store.Config.Dolphin) });
        }
        public static bool Running() {
            foreach (Process p in Process.GetProcesses()) { try { if (p.ProcessName.IndexOf("dolphin", StringComparison.OrdinalIgnoreCase) >= 0) return true; } catch { } finally { p.Dispose(); } } return false;
        }
    }

    public static class Diagnostics {
        static readonly object Gate = new object();
        public static string LogPath { get { return Path.Combine(Constants.Data, "launcher.log"); } }
        public static void Log(string text) {
            lock (Gate) try { Directory.CreateDirectory(Constants.Data); if (File.Exists(LogPath) && new FileInfo(LogPath).Length > 2 * 1024 * 1024) { Util.DeleteFile(LogPath + ".previous"); File.Move(LogPath, LogPath + ".previous"); } File.AppendAllText(LogPath, DateTimeOffset.Now.ToString("O") + " " + Util.Redact(text) + "\r\n", Encoding.UTF8); } catch { }
        }
        public static string Report(Store store, string state, string comments) {
            StringBuilder b = new StringBuilder(); b.AppendLine("RogueMelee-v2 session / problem report"); b.AppendLine("Created UTC: " + DateTimeOffset.UtcNow.ToString("O")); b.AppendLine("Launcher: " + Constants.Version); b.AppendLine("Repository: " + Constants.Repo); b.AppendLine("State: " + state); b.AppendLine("OS: " + Environment.OSVersion); b.AppendLine("64-bit OS: " + Environment.Is64BitOperatingSystem); b.AppendLine("Processor count: " + Environment.ProcessorCount);
            Install current = store.Current; if (current != null) { b.AppendLine("Build: " + current.Tag); b.AppendLine("Release ID: " + current.ReleaseId); b.AppendLine("Game commit: " + current.GitCommit); b.AppendLine("Expected ISO SHA256: " + current.OutputSHA256); b.AppendLine("ISO bytes: " + current.OutputBytes); }
            try { if (File.Exists(store.Config.Dolphin)) { FileVersionInfo v = FileVersionInfo.GetVersionInfo(store.Config.Dolphin); b.AppendLine("Emulator: " + Path.GetFileName(store.Config.Dolphin)); b.AppendLine("Emulator version: " + v.FileVersion); } } catch { }
            if (!String.IsNullOrWhiteSpace(comments)) { b.AppendLine(); b.AppendLine("Tester notes (include seed / floor / fighter / equipped moves):"); b.AppendLine(comments); }
            b.AppendLine(); b.AppendLine("=== Launcher log tail ==="); b.AppendLine(Util.Tail(LogPath, 64 * 1024)); b.AppendLine(); b.AppendLine("=== This launcher's Dolphin log tail ==="); b.AppendLine(Util.Tail(Path.Combine(Constants.Profile, "Logs", "dolphin.log"), 192 * 1024)); b.AppendLine(); b.AppendLine("This report is saved locally. Nothing is uploaded automatically."); return Util.Redact(b.ToString());
        }
        public static void SaveSession(Store store, string state) {
            try { Directory.CreateDirectory(Constants.Reports); Util.AtomicText(Path.Combine(Constants.Reports, "Last session report.txt"), Report(store, state, "")); } catch { }
        }
    }

    public sealed class SettingsDialog : Form {
        readonly TextBox source = new TextBox(), dolphin = new TextBox(), output = new TextBox();
        readonly CheckBox testing = new CheckBox(), autoPlay = new CheckBox(), autoUpdate = new CheckBox();
        readonly Store store;
        public SettingsDialog(Store current) {
            store = current; Text = "RogueMelee v2 - Setup"; Font = new Font("Segoe UI", 10); AutoScaleMode = AutoScaleMode.Dpi; ClientSize = new Size(720, 390); FormBorderStyle = FormBorderStyle.FixedDialog; MaximizeBox = false; MinimizeBox = false; StartPosition = FormStartPosition.CenterParent;
            Label intro = new Label { Text = "Select your clean image once. The original is never patched or overwritten.", AutoSize = true, Location = new Point(20, 16) }; Controls.Add(intro);
            AddPath("Original Melee 1.02 ISO / RVZ", source, 48, delegate { using (OpenFileDialog d = new OpenFileDialog { Title = "Select ORIGINAL clean NTSC-U Melee 1.02", Filter = "Melee source image|*.iso;*.gcm;*.rvz", CheckFileExists = true }) if (d.ShowDialog(this) == DialogResult.OK) source.Text = d.FileName; });
            AddPath("Actual Dolphin.exe / Slippi Dolphin.exe (optional for update-only)", dolphin, 114, delegate { using (OpenFileDialog d = new OpenFileDialog { Title = "Select actual Dolphin executable beside its Sys folder", Filter = "Dolphin|Dolphin.exe;Slippi Dolphin.exe|Executables|*.exe", CheckFileExists = true }) if (d.ShowDialog(this) == DialogResult.OK) dolphin.Text = d.FileName; });
            AddPath("Separate modded ISO output", output, 180, delegate { using (SaveFileDialog d = new SaveFileDialog { Title = "Choose where the modded game goes", Filter = "GameCube ISO|*.iso", FileName = "RogueMelee-v2.iso", OverwritePrompt = true }) if (d.ShowDialog(this) == DialogResult.OK) output.Text = d.FileName; });
            source.Text = store.Config.Source; dolphin.Text = store.Config.Dolphin; output.Text = store.Config.Output;
            testing.Text = "Include published testing / prerelease builds"; testing.SetBounds(22, 247, 650, 26); testing.Checked = store.Config.Testing; Controls.Add(testing);
            autoUpdate.Text = "Automatically install new builds when the launcher opens"; autoUpdate.SetBounds(22, 275, 650, 26); autoUpdate.Checked = store.Config.AutoUpdate; Controls.Add(autoUpdate);
            autoPlay.Text = "Automatically launch after checking / updating (requires Dolphin)"; autoPlay.SetBounds(22, 303, 650, 26); autoPlay.Checked = store.Config.AutoPlay; Controls.Add(autoPlay);
            Button save = new Button { Text = "Save", Location = new Point(484, 348), Size = new Size(100, 30) }; save.Click += Save; Controls.Add(save);
            Button close = new Button { Text = "Cancel", DialogResult = DialogResult.Cancel, Location = new Point(595, 348), Size = new Size(100, 30) }; Controls.Add(close); AcceptButton = save; CancelButton = close;
        }
        void AddPath(string title, TextBox box, int y, EventHandler browse) { Controls.Add(new Label { Text = title, Location = new Point(20, y), AutoSize = true }); box.SetBounds(20, y + 25, 578, 27); Controls.Add(box); Button b = new Button { Text = "Browse...", Location = new Point(608, y + 24), Size = new Size(87, 29) }; b.Click += browse; Controls.Add(b); }
        void Save(object sender, EventArgs e) {
            try {
                string src = source.Text.Trim(), emu = dolphin.Text.Trim(), dst = output.Text.Trim();
                if (src.Length > 0 && !File.Exists(src)) throw new IOException("The source image was not found.");
                if (emu.Length > 0 && !Emulator.ValidExecutable(emu)) throw new IOException("Select the actual Dolphin.exe or Slippi Dolphin.exe beside its Sys folder, not the Slippi Launcher.");
                if (dst.Length == 0 || !Path.IsPathRooted(dst) || !String.Equals(Path.GetExtension(dst), ".iso", StringComparison.OrdinalIgnoreCase)) throw new IOException("Choose an absolute .iso output path.");
                if (Util.SamePath(src, dst)) throw new IOException("The mod output must be different from your clean source image.");
                if (File.Exists(dst) && (store.Current == null || !Util.SamePath(store.Current.Output, dst))) throw new IOException("That output file is not owned by this launcher. Choose a different filename to preserve it.");
                if (!String.Equals(emu, store.Config.Dolphin, StringComparison.OrdinalIgnoreCase)) store.Config.ControllerImportAttempted = false;
                store.Config.Source = src; store.Config.Dolphin = emu; store.Config.Output = Path.GetFullPath(dst); store.Config.Testing = testing.Checked; store.Config.AutoPlay = autoPlay.Checked; store.Config.AutoUpdate = autoUpdate.Checked; store.Save(); DialogResult = DialogResult.OK; Close();
            } catch (Exception ex) { MessageBox.Show(this, ex.Message, "Check setup", MessageBoxButtons.OK, MessageBoxIcon.Warning); }
        }
    }

    public sealed class MainForm : Form {
        Store store; Package latest; CancellationTokenSource cancel; bool busy; Process emulator; string sessionState = "Launcher opened";
        readonly Label installed = new Label(), newest = new Label(), status = new Label(), location = new Label();
        readonly ProgressBar progress = new ProgressBar(); readonly TextBox notes = new TextBox();
        readonly Button primary = new Button(), updateOnly = new Button(), offline = new Button(), check = new Button(), settings = new Button(), controls = new Button(), folder = new Button(), report = new Button(), shortcut = new Button(), rollback = new Button(), stop = new Button(), repair = new Button();
        readonly Action<ProgressInfo> notify;
        public MainForm(Store s) {
            store = s; Text = "RogueMelee v2"; Font = new Font("Segoe UI", 10); AutoScaleMode = AutoScaleMode.Dpi; ClientSize = new Size(780, 592); MinimumSize = new Size(796, 630); FormBorderStyle = FormBorderStyle.FixedSingle; MaximizeBox = false; StartPosition = FormStartPosition.CenterScreen; BackColor = Color.FromArgb(245, 246, 250);
            try { Icon = System.Drawing.Icon.ExtractAssociatedIcon(Program.EntryPath); } catch { }
            Panel header = new Panel { BackColor = Color.FromArgb(20, 29, 48), Dock = DockStyle.Top, Height = 88 }; Controls.Add(header);
            header.Controls.Add(new Label { Text = "ROGUEMELEE  v2", ForeColor = Color.White, Font = new Font("Segoe UI", 22, FontStyle.Bold), Location = new Point(22, 13), AutoSize = true });
            header.Controls.Add(new Label { Text = "Install once. Check for new builds every launch.", ForeColor = Color.FromArgb(216, 222, 235), Location = new Point(26, 55), AutoSize = true });
            installed.SetBounds(25, 103, 724, 24); newest.SetBounds(25, 132, 724, 24); location.SetBounds(25, 165, 720, 28); location.AutoEllipsis = true; location.ForeColor = Color.DimGray; Controls.Add(installed); Controls.Add(newest); Controls.Add(location);
            notes.SetBounds(25, 201, 730, 146); notes.Multiline = true; notes.ReadOnly = true; notes.ScrollBars = ScrollBars.Vertical; notes.BackColor = Color.White; notes.Text = "Checking releases..."; Controls.Add(notes);
            status.SetBounds(25, 359, 730, 43); status.AutoEllipsis = true; status.Text = "Starting..."; Controls.Add(status); progress.SetBounds(25, 403, 730, 14); Controls.Add(progress);
            AddButton(primary, "Install & Play", 25, 433, 220, 42, async delegate { await StartInstall(true, false); }); primary.BackColor = Color.FromArgb(242, 197, 57); primary.FlatStyle = FlatStyle.Flat; primary.Font = new Font("Segoe UI", 11, FontStyle.Bold);
            AddButton(updateOnly, "Install / Update only", 255, 433, 182, 42, async delegate { await StartInstall(false, false); });
            AddButton(offline, "Play installed (offline)", 447, 433, 194, 42, async delegate { await LaunchGame(); });
            AddButton(stop, "Cancel", 651, 433, 104, 42, delegate { if (cancel != null) { cancel.Cancel(); status.Text = "Cancelling safely..."; } });
            AddButton(check, "Check again", 25, 489, 115, 32, async delegate { await CheckUpdates(false); });
            AddButton(settings, "Setup", 148, 489, 90, 32, delegate { Setup(); });
            AddButton(controls, "Controllers", 246, 489, 112, 32, delegate { ConfigureController(); });
            AddButton(folder, "Game folder", 366, 489, 114, 32, delegate { OpenFolder(Path.GetDirectoryName(store.Config.Output)); });
            AddButton(report, "Report problem", 488, 489, 128, 32, delegate { ExportReport(); });
            AddButton(shortcut, "Desktop shortcut", 624, 489, 131, 32, delegate { CreateShortcut(); });
            AddButton(rollback, "Restore previous build", 25, 534, 187, 30, async delegate { await RestorePrevious(); });
            AddButton(repair, "Repair installation", 222, 534, 163, 30, async delegate { await StartInstall(false, true); });
            LinkLabel releases = new LinkLabel { Text = "GitHub releases", Location = new Point(602, 542), AutoSize = true }; releases.LinkClicked += delegate { Process.Start(new ProcessStartInfo(Constants.Releases) { UseShellExecute = true }); }; Controls.Add(releases);
            notify = p => { if (!IsDisposed && IsHandleCreated) { try { BeginInvoke(new Action(delegate { OnProgress(p); })); } catch (InvalidOperationException) { } } };
            Shown += async delegate { try { SetBusy(true); await Task.Run(() => store.Recover(cancel.Token, notify)); } catch (Exception ex) { ShowError(ex); } finally { SetBusy(false); } await CheckUpdates(true); };
            FormClosing += OnClosing; RefreshState();
        }
        void AddButton(Button button, string text, int x, int y, int w, int h, EventHandler handler) { button.Text = text; button.SetBounds(x, y, w, h); button.Click += handler; Controls.Add(button); }
        void OnProgress(ProgressInfo p) { if (IsDisposed) return; status.Text = p.Text; if (p.Percent < 0) { progress.Style = ProgressBarStyle.Marquee; progress.MarqueeAnimationSpeed = 25; } else { progress.Style = ProgressBarStyle.Continuous; progress.Value = Math.Max(0, Math.Min(100, p.Percent)); } }
        bool IsPlaying { get { try { return emulator != null && !emulator.HasExited; } catch { return false; } } }
        void SetBusy(bool value) { busy = value; if (value) { cancel = new CancellationTokenSource(); } else { if (cancel != null) cancel.Dispose(); cancel = null; progress.Style = ProgressBarStyle.Continuous; progress.Value = 0; } RefreshState(); }
        void RefreshState() {
            installed.Text = "Installed:  " + (store.HasInstall ? store.Current.Tag : "Not installed yet");
            newest.Text = "Latest:  " + (latest == null ? "No release selected" : latest.Release.Tag + (latest.Release.Prerelease ? "  (testing)" : "  (stable)"));
            location.Text = store.HasInstall ? store.Current.Output : "Output: " + store.Config.Output;
            primary.Text = store.HasInstall ? "Update & Play" : "Install & Play"; bool ready = !busy && !IsPlaying;
            primary.Enabled = ready; updateOnly.Enabled = ready; offline.Enabled = ready && store.HasInstall; settings.Enabled = ready; check.Enabled = ready; controls.Enabled = ready; rollback.Enabled = ready && File.Exists(store.PreviousPath) && store.HasInstall; repair.Enabled = ready && store.HasInstall; stop.Enabled = busy; folder.Enabled = true; shortcut.Enabled = !busy; report.Enabled = true;
        }
        bool Setup() { if (busy || IsPlaying) return false; using (SettingsDialog d = new SettingsDialog(store)) { bool accepted = d.ShowDialog(this) == DialogResult.OK; RefreshState(); if (accepted) { latest = null; notes.Text = "Setup saved. Choose Install & Play, Install / Update only, or Check again."; status.Text = "Setup saved."; RefreshState(); } return accepted; } }
        async Task CheckUpdates(bool automatic) {
            if (busy || IsPlaying) return; SetBusy(true); bool good = false;
            try { latest = await Task.Run(() => Network.Latest(store.Config.Testing, cancel.Token, notify)); good = true;
                if (latest == null) { notes.Text = "There are no published " + (store.Config.Testing ? "testing or stable" : "stable") + " releases yet.\r\n\r\nJosh must publish the .xdelta patch and build-manifest.json as assets of a GitHub Release. Pushing source code alone is not an update.\r\n\r\nKeep this EXE. Check again after the first release is published."; status.Text = "Waiting for the first published release."; }
                else { notes.Text = (latest.Release.Name.Length > 0 ? latest.Release.Name + "\r\n" : "") + latest.Release.Published.ToLocalTime().ToString("g") + "\r\n\r\n" + latest.Release.Body; status.Text = store.HasInstall && store.Current.Fingerprint == latest.Fingerprint ? "Installed build is current." : "Ready to install " + latest.Release.Tag + "."; Diagnostics.Log("Discovered release " + latest.Release.Id + " / " + latest.Release.Tag); }
            } catch (OperationCanceledException) { status.Text = "Check cancelled."; } catch (Exception ex) { ShowError(ex, !automatic); status.Text = store.HasInstall ? "Update check failed. Play installed works offline." : "Cannot check releases. See the status / launcher report."; notes.Text = ex.Message; }
            finally { SetBusy(false); }
            if (!automatic || !good || latest == null || !store.HasInstall) return;
            if (store.Config.PausedRelease == latest.Release.Id && store.Current.Fingerprint != latest.Fingerprint) { status.Text = "Rolled-back build selected. This release is paused; a newer release will update normally."; if (store.Config.AutoPlay && Emulator.ValidExecutable(store.Config.Dolphin)) await LaunchGame(); return; }
            if (store.Config.AutoUpdate && (store.Current.Fingerprint == latest.Fingerprint || File.Exists(store.Config.Source))) await StartInstall(store.Config.AutoPlay && Emulator.ValidExecutable(store.Config.Dolphin), false);
            else if (store.Config.AutoPlay && store.Current.Fingerprint == latest.Fingerprint && Emulator.ValidExecutable(store.Config.Dolphin)) await LaunchGame();
            else if (store.Current.Fingerprint != latest.Fingerprint && !File.Exists(store.Config.Source)) status.Text = "New build available. Reconnect your clean source ISO, then click Update.";
        }
        bool EnsureNoEmulator() { if (Emulator.Running()) { MessageBox.Show(this, "Close Dolphin / Slippi before installing, changing profiles, or launching another session. The updater never replaces an ISO while an emulator may be reading it.", "Close the emulator first", MessageBoxButtons.OK, MessageBoxIcon.Information); return false; } return true; }
        async Task StartInstall(bool play, bool repairing) {
            if (busy || IsPlaying || !EnsureNoEmulator()) return;
            if (File.Exists(store.JournalPath)) { MessageBox.Show(this, "An interrupted update needs recovery. Restart the launcher before installing again.", "Recovery needed"); return; }
            if (repairing && MessageBox.Show(this, "Rebuild the latest release from the clean source? The existing ISO will be kept as .previous, but a damaged ISO is not a usable rollback. This replaces the older rollback slot.", "Repair installation", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) return;
            bool needsSource = repairing || !store.HasInstall || latest == null || store.Current.Fingerprint != latest.Fingerprint || !Util.SamePath(store.Current.Output, store.Config.Output);
            if (!store.HasInstall || (needsSource && !File.Exists(store.Config.Source)) || (play && !Emulator.ValidExecutable(store.Config.Dolphin))) { if (!Setup()) return; }
            if (play && !Emulator.ValidExecutable(store.Config.Dolphin)) { status.Text = "Choose a Dolphin executable in Setup, or select Install / Update only."; return; }
            SetBusy(true); bool success = false;
            try {
                if (latest == null) latest = await Task.Run(() => Network.Latest(store.Config.Testing, cancel.Token, notify));
                if (latest == null) { status.Text = "No published releases yet. Josh needs to publish the first patch."; notes.Text = "The repository is public, but it has no published patch release. Keep this EXE and retry after Josh publishes one."; return; }
                if (!repairing && store.HasInstall && store.Current.Fingerprint == latest.Fingerprint && Util.SamePath(store.Current.Output, store.Config.Output)) { status.Text = "Already on " + latest.Release.Tag + "."; success = true; }
                else {
                    if (!File.Exists(store.Config.Source)) throw new IOException("A clean Melee ISO is required for installation or updating. Choose it in Setup.");
                    if (store.HasInstall && store.Current.ReleaseId > latest.Release.Id && MessageBox.Show(this, "The selected release is older than the installed release. Install " + latest.Release.Tag + " anyway?", "Confirm downgrade", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) return;
                    CancellationToken token = cancel.Token; await Task.Run(() => Engine.Apply(store, latest, token, notify, repairing));
                    store.Config.PausedRelease = 0; store.Save(); Diagnostics.Log("Installed " + store.Current.Tag + ", verified " + store.Current.OutputSHA256); status.Text = "Installed " + store.Current.Tag + ". Ready to play."; success = true;
                }
            } catch (OperationCanceledException) { status.Text = "Cancelled. The previous game was not replaced unless promotion already finished."; }
            catch (Exception ex) { ShowError(ex); status.Text = "Install failed. Your clean ISO was not modified. Play the previous build or retry."; }
            finally { SetBusy(false); }
            if (success && play) await LaunchGame();
        }
        async Task LaunchGame() {
            if (busy || IsPlaying || !store.HasInstall || !EnsureNoEmulator()) return;
            if (!Emulator.ValidExecutable(store.Config.Dolphin) && !Setup()) return; if (!Emulator.ValidExecutable(store.Config.Dolphin)) { status.Text = "Dolphin is optional for update-only; select it in Setup to launch."; return; }
            SetBusy(true);
            try {
                await Task.Run(() => Engine.VerifyInstall(store.Current, cancel.Token, notify));
                sessionState = "Launching " + store.Current.Tag; Diagnostics.Log(sessionState); Diagnostics.SaveSession(store, sessionState);
                emulator = Emulator.Start(store, false); sessionState = "Game running; PID " + emulator.Id; Diagnostics.SaveSession(store, sessionState); status.Text = "Game running. Report problem also works during a freeze.";
            } catch (OperationCanceledException) { status.Text = "Launch cancelled."; } catch (Exception ex) { ShowError(ex); emulator = null; }
            finally { SetBusy(false); }
            if (emulator != null) { Process current = emulator; try { await Task.Run(delegate { current.WaitForExit(); }); int exit = current.ExitCode; sessionState = "Emulator exited " + exit + " (0x" + exit.ToString("X8") + ")"; Diagnostics.Log(sessionState); Diagnostics.SaveSession(store, sessionState); status.Text = exit == 0 ? "Session ended. Ready for another run." : "Emulator ended unexpectedly. Use Report problem to save the diagnostics."; } catch (Exception ex) { Diagnostics.Log(ex.ToString()); } finally { current.Dispose(); emulator = null; RefreshState(); } }
        }
        void ConfigureController() { if (busy || IsPlaying || !EnsureNoEmulator()) return; if (!Emulator.ValidExecutable(store.Config.Dolphin) && !Setup()) return; try { Emulator.Start(store, true); status.Text = "Configure Controllers in the opened Dolphin window, then close it and choose Play."; } catch (Exception ex) { ShowError(ex); } }
        async Task RestorePrevious() {
            if (busy || !EnsureNoEmulator()) return;
            if (MessageBox.Show(this, "Restore the previous verified game build? The currently installed release will be skipped during automatic updates until a newer release appears. Click Update manually to retry it.", "Restore previous build", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) return;
            SetBusy(true); try { await Task.Run(() => Engine.Rollback(store, cancel.Token, notify)); status.Text = "Previous build restored. Click Play installed."; Diagnostics.Log("Rolled back to " + store.Current.Tag); } catch (Exception ex) { ShowError(ex); } finally { SetBusy(false); }
        }
        void ShowError(Exception ex, bool dialog = true) { Diagnostics.Log(ex.ToString()); sessionState = "Launcher error: " + ex.Message; Diagnostics.SaveSession(store, sessionState); if (dialog) MessageBox.Show(this, ex.Message, "RogueMelee v2", MessageBoxButtons.OK, MessageBoxIcon.Warning); }
        void OpenFolder(string path) { try { Directory.CreateDirectory(path); Process.Start(new ProcessStartInfo("explorer.exe", Util.Quote(path)) { UseShellExecute = true }); } catch (Exception ex) { ShowError(ex); } }
        void ExportReport() {
            using (Form form = new Form { Text = "Report a problem", Font = Font, ClientSize = new Size(640, 385), StartPosition = FormStartPosition.CenterParent, MinimizeBox = false, MaximizeBox = false }) {
                form.Controls.Add(new Label { Text = "What happened? Include seed, floor, fighter, moves and steps when possible.", Location = new Point(18, 16), Size = new Size(600, 43) });
                TextBox comments = new TextBox { Multiline = true, ScrollBars = ScrollBars.Vertical, Location = new Point(18, 61), Size = new Size(604, 213) }; form.Controls.Add(comments);
                form.Controls.Add(new Label { Text = "Contains build details and recent local logs; no ISO, save or credentials.\r\nNothing is uploaded. Review the text before sharing it with Josh.", Location = new Point(18, 282), Size = new Size(604, 44) });
                Button save = new Button { Text = "Save report ZIP", Location = new Point(18, 338), Size = new Size(158, 32) }; form.Controls.Add(save);
                Button copy = new Button { Text = "Copy report", Location = new Point(188, 338), Size = new Size(135, 32) }; form.Controls.Add(copy);
                Button open = new Button { Text = "Open reports folder", Location = new Point(336, 338), Size = new Size(178, 32) }; form.Controls.Add(open);
                copy.Click += delegate { try { string text = Diagnostics.Report(store, sessionState, comments.Text); Clipboard.SetText(text); Util.AtomicText(Path.Combine(Constants.Reports, "Last session report.txt"), text); } catch (Exception ex) { ShowError(ex); } };
                open.Click += delegate { OpenFolder(Constants.Reports); };
                save.Click += delegate { try { string text = Diagnostics.Report(store, sessionState, comments.Text); Util.AtomicText(Path.Combine(Constants.Reports, "Last session report.txt"), text); using (SaveFileDialog d = new SaveFileDialog { Title = "Save diagnostics to send to Josh", Filter = "ZIP archive|*.zip", FileName = "RogueMelee-v2-report-" + DateTime.Now.ToString("yyyyMMdd-HHmmss") + ".zip", InitialDirectory = Constants.Reports }) { if (d.ShowDialog(form) != DialogResult.OK) return; using (FileStream output = new FileStream(d.FileName, FileMode.Create)) using (ZipArchive zip = new ZipArchive(output, ZipArchiveMode.Create)) using (StreamWriter writer = new StreamWriter(zip.CreateEntry("Report.txt").Open(), new UTF8Encoding(false))) writer.Write(text); } } catch (Exception ex) { ShowError(ex); } };
                form.ShowDialog(this);
            }
        }
        void CreateShortcut() {
            try {
                string source = Program.EntryPath, dest = Path.Combine(Constants.Data, "RogueMelee-v2.exe"); if (!Util.SamePath(source, dest)) File.Copy(source, dest, true);
                Type type = Type.GetTypeFromProgID("WScript.Shell"); object shell = Activator.CreateInstance(type), link = null;
                try {
                    string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory), "RogueMelee v2.lnk");
                    link = type.InvokeMember("CreateShortcut", BindingFlags.InvokeMethod, null, shell, new object[] { path }); Type lt = link.GetType();
                    lt.InvokeMember("TargetPath", BindingFlags.SetProperty, null, link, new object[] { dest }); lt.InvokeMember("WorkingDirectory", BindingFlags.SetProperty, null, link, new object[] { Constants.Data }); lt.InvokeMember("Description", BindingFlags.SetProperty, null, link, new object[] { "Check for the latest RogueMelee v2 test build and play" }); lt.InvokeMember("Save", BindingFlags.InvokeMethod, null, link, null);
                } finally { if (link != null) Marshal.FinalReleaseComObject(link); Marshal.FinalReleaseComObject(shell); }
                status.Text = "Desktop shortcut created. Keep using it for future builds.";
            } catch (Exception ex) { ShowError(ex); }
        }
        void OnClosing(object sender, FormClosingEventArgs e) {
            if (busy) { e.Cancel = true; if (cancel != null) cancel.Cancel(); status.Text = "Cancelling. Close again after the operation finishes."; }
            else if (IsPlaying) { if (MessageBox.Show(this, "Close only the launcher? Dolphin will keep running, but the final session report will not update after it closes.", "Game is still running", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) e.Cancel = true; else Diagnostics.SaveSession(store, "Launcher closed while game was running; use the Dolphin log for later events."); }
        }
    }

    public static class Program {
        public static string EntryPath;
        [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
        [STAThread] public static void Main(string[] args) {
            EntryPath = Application.ExecutablePath;
            for (int i = 0; i + 1 < args.Length; i++) if (args[i] == "--launcher" && File.Exists(args[i + 1])) EntryPath = Path.GetFullPath(args[i + 1]);
            if (args.Contains("--self-test")) { try { SelfTests.Run(args); Environment.ExitCode = 0; } catch (Exception ex) { Console.Error.WriteLine(ex); Environment.ExitCode = 1; } return; }
            bool created; using (Mutex mutex = new Mutex(true, "Local\\RogueMelee-v2-Friends-Launcher", out created)) {
                if (!created) { MessageBox.Show("RogueMelee v2 is already open. Use the existing launcher window.", "RogueMelee v2"); return; }
                try { SetProcessDPIAware(); Application.EnableVisualStyles(); Application.SetCompatibleTextRenderingDefault(false); ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12; ServicePointManager.DefaultConnectionLimit = 4; Diagnostics.Log("Launcher " + Constants.Version + " starting"); Application.Run(new MainForm(new Store())); }
                catch (Exception ex) { Diagnostics.Log(ex.ToString()); MessageBox.Show(ex.Message + "\r\n\r\nDetails: " + Diagnostics.LogPath, "RogueMelee v2 could not start", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
        }
    }

    public static class SelfTests {
        static int count;
        static void Check(bool b, string name) { if (!b) throw new Exception("FAILED: " + name); count++; }
        static void Reject(Action action, string name) { bool rejected = false; try { action(); } catch { rejected = true; } Check(rejected, name); }
        public static void Run(string[] args) {
            Check(Util.Quote("C:\\Games\\Melee.iso") == "\"C:\\Games\\Melee.iso\"", "quote ordinary path");
            Check(Util.Quote("C:\\Space Dir\\") == "\"C:\\Space Dir\\\\\"", "quote trailing slash");
            Check(Util.Quote("a\"b") == "\"a\\\"b\"", "quote embedded quote");
            Check(Util.IsHash(new string('a', 64), 64), "valid SHA256"); Check(!Util.IsHash(new string('a', 63), 64), "reject short SHA256"); Check(!Util.IsHash(new string('g', 64), 64), "reject non-hex SHA256");
            Reject(() => Network.ValidateUrl("http://github.com/test", false), "reject HTTP"); Reject(() => Network.ValidateUrl("https://github.com.evil.example/file", false), "reject host suffix"); Reject(() => Network.ValidateUrl("https://user:pass@github.com/file", false), "reject userinfo"); Reject(() => Network.ValidateUrl("https://github.com/another/repo/releases/download/v1/p.xdelta", true), "reject other repository");
            Network.ValidateUrl("https://github.com/" + Constants.Repo + "/releases/download/test/p.xdelta", true); count++;
            string releases = "[{\"id\":1,\"tag_name\":\"v1\",\"name\":\"stable\",\"body\":\"\",\"draft\":false,\"prerelease\":false,\"published_at\":\"2026-01-01T00:00:00Z\",\"assets\":[]},{\"id\":2,\"tag_name\":\"test2\",\"draft\":false,\"prerelease\":true,\"published_at\":\"2026-02-01T00:00:00Z\",\"assets\":[]},{\"id\":3,\"tag_name\":\"draft3\",\"draft\":true,\"prerelease\":false,\"published_at\":\"2026-03-01T00:00:00Z\",\"assets\":[]}]";
            Check(Network.ParseReleases(releases, true).Count == 2, "ignore drafts"); Check(Network.ParseReleases(releases, true)[0].Id == 2, "testing build selected by publication time"); Check(Network.ParseReleases(releases, false)[0].Id == 1, "stable filter"); Check(Network.ParseReleases("[]", true).Count == 0, "empty feed");
            Release r = new Release { Id = 42, Tag = "test" }; r.Assets.Add(new Asset { Id = 4, Name = "rogueMelee-v0.1.0.xdelta", Size = 5, Url = "https://github.com/" + Constants.Repo + "/releases/download/test/rogueMelee-v0.1.0.xdelta" });
            string manifest = "{\"patch_sha256\":\"" + new string('a', 64) + "\",\"output_sha256\":\"" + new string('b', 64) + "\"}";
            Package p = Network.ParsePackage(r, manifest); Check(p.OutputSHA256 == new string('b', 64), "native v2 manifest supported");
            Reject(() => Network.ParsePackage(r, "{}"), "missing hashes"); Reject(() => Network.ParsePackage(r, "{\"launcher_schema\":2}"), "unknown schema");
            r.Assets[0].Digest = "sha256:" + new string('c', 64); Reject(() => Network.ParsePackage(r, manifest), "GitHub digest mismatch"); r.Assets[0].Digest = "";
            r.Assets.Add(new Asset { Id = 5, Name = "other.xdelta", Size = 5, Url = r.Assets[0].Url }); Reject(() => Network.ParsePackage(r, manifest), "ambiguous patches");
            string named = manifest.Substring(0, manifest.Length - 1) + ",\"patch_file\":\"rogueMelee-v0.1.0.xdelta\"}"; Check(Network.ParsePackage(r, named).Patch.Id == 4, "explicit patch selector");
            string dir = Path.Combine(Path.GetTempPath(), "rogue-launcher-test-" + Guid.NewGuid().ToString("N")); Directory.CreateDirectory(dir);
            try { string file = Path.Combine(dir, "hash.txt"); File.WriteAllText(file, "abc", new UTF8Encoding(false)); Check(Util.HashFile(file, "SHA256", CancellationToken.None, null, "") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", "SHA256 streaming"); Check(Util.HashFile(file, "MD5", CancellationToken.None, null, "") == "900150983cd24fb0d6963f7d28e17f72", "MD5 streaming");
                string json = Path.Combine(dir, "settings.json"); Util.SaveJson(json, new Settings { Source = "D:\\Games\\a b.iso" }); Check(Util.LoadJson<Settings>(json).Source == "D:\\Games\\a b.iso", "settings path roundtrip"); Util.SaveJson(json, new Settings { Source = "new.iso" }); Check(Util.LoadJson<Settings>(json).Source == "new.iso", "atomic JSON replacement");
                Reject(() => Util.VerifySource(file, CancellationToken.None, null), "reject non-Melee source");
                string target = Path.Combine(dir, "target.iso"), newer = Path.Combine(dir, "new.iso"), backup = target + ".previous"; File.WriteAllText(target, "previous"); File.WriteAllText(newer, "next"); File.Replace(newer, target, backup, true); Check(File.ReadAllText(target) == "next" && File.ReadAllText(backup) == "previous", "atomic install plus backup");
            } finally { Directory.Delete(dir, true); }
            string message = "PASS " + count + " launcher self-tests (no network, game, or emulator required)."; Console.WriteLine(message); for (int i = 0; i + 1 < args.Length; i++) if (args[i] == "--report") File.WriteAllText(args[i + 1], message + "\r\n");
        }
    }
}
